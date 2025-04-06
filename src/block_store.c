#include <stdio.h>
#include <stdint.h>

#include "bitmap.h"
#include "block_store.h"
// include more if you need

struct block_store
{
	uint8_t *blocks; //Each point in the array represents a byte of data, every 4 bytes or uint8_t should be a block
	bitmap_t *fbm; //Represents the free block manager
};

// You might find this handy. I put it around unused parameters, but you should
// remove it before you submit. Just allows things to compile initially.
#define UNUSED(x) (void)(x)

block_store_t *block_store_create()
{
	block_store_t *bs = (block_store_t *)malloc(sizeof(block_store_t));
	if(bs == NULL)
	{
		return NULL; //Failed allocation.
	}

	bs->blocks  = (uint8_t *)calloc(BLOCK_STORE_NUM_BLOCKS, BLOCK_SIZE_BYTES);
        if(bs->blocks == NULL)
        {	
			free(bs);
           	return NULL; //Failed allocation
        }


	bs->fbm = bitmap_overlay(BITMAP_SIZE_BITS, bs->blocks +  BITMAP_START_BLOCK); //This creates a bitmap depending on the total number of bytes from the set of blocks

	if(bs->fbm == NULL)
	{	
		free(bs->blocks);		
	   	free(bs); //Free the allocated data
		return NULL; //Failed allocation
	}
	

	for(size_t i = BITMAP_START_BLOCK; i < BITMAP_START_BLOCK + BITMAP_NUM_BLOCKS; i++)
	{
		bitmap_set(bs->fbm, i); // We set up the bitmap at the starting block position and allocate any additional space
	}

	return bs;
}


void block_store_destroy(block_store_t *const bs)
{
 	if(bs){
		bitmap_destroy(bs->fbm); //Frees the bitmap
		free(bs->blocks); //Fress the block data
		free(bs); //Frees the block_store_t object
	}
}

size_t block_store_allocate(block_store_t *const bs)
{
	if(bs == NULL || bs->fbm == NULL)
	{
		return SIZE_MAX; //If our block store is null then we return null
	}
 
	size_t block_id = bitmap_ffz(bs->fbm); //We seek out the first zero bit (i.e. the next bit that hasn't been allocated)

	if(block_id == SIZE_MAX)
	{
		return SIZE_MAX; //We return this if all bits have been allocated
	}
	
	
	bitmap_set(bs->fbm, block_id); //Allocate the bit on the bitmap at the next zero bit found in block_id if all bits haven't been allocated

	return block_id; //Return the id of the block that was allocated on the bitmap
}

bool block_store_request(block_store_t *const bs, const size_t block_id)
{	
	if(bs != NULL) //Check to seen if the block store is null if it is we assume that the bitmap is allocated since that would have to been allocated to a block store via the block store create function
	{
		if(block_id < BLOCK_STORE_NUM_BLOCKS) //Check if in-bounds
		{
			if(bitmap_test(bs->fbm, block_id) == false) //We see if the bit hasn't been allocated
			{
				bitmap_set(bs->fbm, block_id); //Allocate the bit on the bitmap
				return true; //Return true since the requested bit was allocated through the request
			}
		}
	}
	return false; //Since block store is null there is nothing to find or that block has been allocated
}

void block_store_release(block_store_t *const bs, const size_t block_id)
{
	if(bs != NULL) //511 since we have 512 blocks
        {
		if(block_id < BLOCK_STORE_NUM_BLOCKS ){
			bitmap_reset(bs->fbm, block_id); //We set the bit at the provided position to 0 (i.e. we deallocated it)
		}
	}
}

size_t block_store_get_used_blocks(const block_store_t *const bs)
{
	if(bs == NULL || bs->fbm == NULL)
	{
		return SIZE_MAX; //Return null if either
	}
	return bitmap_total_set(bs->fbm); //Gets the total amount of allocated bits on the bitmap
}

size_t block_store_get_free_blocks(const block_store_t *const bs)
{
	if(bs == NULL || bs->fbm == NULL)
	{
		return SIZE_MAX; //Return null if either
	}
	return BLOCK_STORE_NUM_BLOCKS - bitmap_total_set(bs->fbm); //Finds the total amount of allocated bits and subtracts it by the number of blocks we have to find the number of free blocks
}

size_t block_store_get_total_blocks()
{
	return BLOCK_STORE_NUM_BLOCKS; //Returns this constant because this constant tells us the number of blocks we have
}

size_t block_store_read(const block_store_t *const bs, const size_t block_id, void *buffer)
{
	if(bs == NULL || buffer == NULL || block_id >= BLOCK_STORE_NUM_BLOCKS)
	{
		return 0; //Invalid parameters 
	}

	uint8_t *temp = bs-> blocks + (block_id * BLOCK_SIZE_BYTES); //Gets the starting address to read from
	memcpy(buffer, temp, BLOCK_SIZE_BYTES); //Copies the memory from the address temp to our buffer
	
	return BLOCK_SIZE_BYTES; //Returns the amount of bytes used for copying
}

size_t block_store_write(block_store_t *const bs, const size_t block_id, const void *buffer)
{
	if(bs == NULL || buffer == NULL || block_id >= BLOCK_STORE_NUM_BLOCKS)
	{
		return 0; //Invalid parameters
	}

	//grab the location where we want to write to
	uint8_t *temp = bs-> blocks + (block_id * BLOCK_SIZE_BYTES);

	//this time copy the contents of the buffer into the correct block
	memcpy(temp, buffer, BLOCK_SIZE_BYTES);
	
	return BLOCK_SIZE_BYTES;
}

block_store_t *block_store_deserialize(const char *const filename)
{
	if(filename == NULL)
	{
		return NULL; //Invalid file name
	}

	//read binary file
	FILE *file = fopen(filename, "rb");
	if(file == NULL)
	{
		fclose(file);
		return NULL;
	}

	//new block store
	block_store_t * bs = block_store_create();
	if (bs == NULL)
	{
		fclose(file);
		return NULL;
	}

	//ok, now we can read the blocks
	if (fread(bs-> blocks, 1, BLOCK_STORE_NUM_BYTES, file) != BLOCK_STORE_NUM_BYTES)
	{
		block_store_destroy(bs);
		fclose(file);
		return NULL;
	}

	//recreate bitmap
	bs -> fbm = bitmap_overlay(BITMAP_SIZE_BITS, bs->blocks + BITMAP_START_BLOCK);
	if(bs-> fbm == NULL)
	{
		block_store_destroy(bs);
		fclose(file);
		return NULL;
	}

	fclose(file);
	return bs;
}

size_t block_store_serialize(const block_store_t *const bs, const char *const filename)
{
	if(bs == NULL ||  filename == NULL)
	{
		return 0; //Invalid parameters
	}

	//read binary file to get ready to write to
        FILE* file = fopen(filename, "wb");
        if(file == NULL)
        {
                return 0;
        }

	size_t blocks_written = fwrite(bs->blocks, BLOCK_SIZE_BYTES, BLOCK_STORE_NUM_BLOCKS, file); //We see the amount of blocks written since fwrite takes in the amount of blocks and the total size of those blocks to see what to write from the provide file and struct

	if(blocks_written > block_store_get_total_blocks())
	{
		fclose(file); //Closes the file
		return 0; //Return 0 since we wrote outside our total block range
	}

	fclose(file); //Close the file
	return blocks_written * BLOCK_SIZE_BYTES; //Provides of total bytes used from our blocks written with the amount of bytes per each block
}
