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
		bitmap_set(bs->fbm, i);
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
	if(bs == NULL)
	{
		return SIZE_MAX;
	}
 
	size_t block_id = bitmap_ffz(bs->fbm);

	if(block_id == SIZE_MAX)
	{
		return SIZE_MAX;
	}
	
	
	bitmap_set(bs->fbm, block_id);

	return block_id;
}

bool block_store_request(block_store_t *const bs, const size_t block_id)
{	
	if(bs != NULL)
	{
		if(block_id < BLOCK_STORE_NUM_BLOCKS)
		{
			if(bitmap_test(bs->fbm, block_id) == false)
			{
				bitmap_set(bs->fbm, block_id);
				if(bitmap_test(bs->fbm, block_id) == true)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void block_store_release(block_store_t *const bs, const size_t block_id)
{
	if(bs != NULL) //511 since we have 512 blocks
        {
		if(block_id < BLOCK_STORE_NUM_BLOCKS ){
			bitmap_reset(bs->fbm, block_id);
		}
	}
}

size_t block_store_get_used_blocks(const block_store_t *const bs)
{
	if(bs == NULL || bs->fbm == NULL)
	{
		return SIZE_MAX;
	}
	return bitmap_total_set(bs->fbm);
}

size_t block_store_get_free_blocks(const block_store_t *const bs)
{
	if(bs == NULL || bs->fbm == NULL)
	{
		return SIZE_MAX;
	}
	return BLOCK_STORE_NUM_BLOCKS - bitmap_total_set(bs->fbm);
}

size_t block_store_get_total_blocks()
{
	return BLOCK_STORE_NUM_BLOCKS;
}

size_t block_store_read(const block_store_t *const bs, const size_t block_id, void *buffer)
{
	if(bs == NULL || buffer == NULL || block_id >= BLOCK_STORE_NUM_BLOCKS)
	{
		return 0;
	}

	uint8_t *temp = bs-> blocks + (block_id * BLOCK_SIZE_BYTES);
	memcpy(buffer, temp, BLOCK_SIZE_BYTES);
	
	return BLOCK_SIZE_BYTES;
}

size_t block_store_write(block_store_t *const bs, const size_t block_id, const void *buffer)
{
	if(bs == NULL || buffer == NULL || block_id >= BLOCK_STORE_NUM_BLOCKS)
	{
		return 0;
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
		return NULL;
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
	UNUSED(bs);
	UNUSED(filename);
	return 0;
}
