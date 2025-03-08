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

	bs->blocks  = (uint8_t *)calloc(BLOCK_STORE_NUM_BLOCKS - 1, BLOCK_SIZE_BYTES);
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

	for(size_t i = 0; i < BLOCK_STORE_NUM_BLOCKS; i++)	
	{
		block_store_request(bs,i);
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
	
	if(block_id >= BITMAP_START_BLOCK + BITMAP_NUM_BLOCKS || block_id<BITMAP_START_BLOCK)
	{
		bitmap_set(bs->fbm, block_id);
		return block_id;
	}

	return SIZE_MAX;
}

bool block_store_request(block_store_t *const bs, const size_t block_id)
{	
	UNUSED(bs);
	UNUSED(block_id);	
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
	UNUSED(bs);
	return 0;
}

size_t block_store_get_free_blocks(const block_store_t *const bs)
{
	UNUSED(bs);
	return 0;
}

size_t block_store_get_total_blocks()
{
	return BLOCK_STORE_NUM_BLOCKS;
}

size_t block_store_read(const block_store_t *const bs, const size_t block_id, void *buffer)
{
	UNUSED(bs);
	UNUSED(block_id);
	UNUSED(buffer);
	return 0;
}

size_t block_store_write(block_store_t *const bs, const size_t block_id, const void *buffer)
{
	UNUSED(bs);
	UNUSED(block_id);
	UNUSED(buffer);
	return 0;
}

block_store_t *block_store_deserialize(const char *const filename)
{
	UNUSED(filename);
	return NULL;
}

size_t block_store_serialize(const block_store_t *const bs, const char *const filename)
{
	UNUSED(bs);
	UNUSED(filename);
	return 0;
}
