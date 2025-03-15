#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <math.h>

#include "utils.h"
#include "freelist.h"
#include "bitmap.h"
#include "error.h"
#include "balloc.h"
#include <stdlib.h>

//struct for representing a memory pool
struct memoryPool {
  unsigned int size; //size of mem pool
  int l, u;   //lower & upper bounds of blocks to be allocated
  unsigned char *memory;  //array of bytes that represents mem pool
  int *freeList; //keep track of what blocks are currently allocated
};

/*
*constructs & returns a new allocator. an application can have multiple.
*memory may not be uniform, differetn characteristics (eg speed)
*size: total number of bytes that can be allocated
*l (lower): specifies the smallest allocation will be 2^l bytes. Even if smaller is requested
*u (upper): specifies the largest allocation will be 2^u bytes. Larger request will fail
*/
extern Balloc bnew(unsigned int size, int l, int u){
  struct memoryPool *pool = (struct memoryPool*)malloc(sizeof(struct memoryPool));  //allocate mem for pool
  pool->size = size;  //initialize pool size
  pool->l = l;  //initialise l & u blocks
  pool->u = u;
  pool->memory = (unsigned char*)malloc(size);  //allocate the mem for pool
  pool->freeList = (int*)malloc(size / l * sizeof(int)); //allocate mem for freelist

  //initialize the free list to indicate that all blocks are free
  for (int i = 0; i < size / l; i++) {
    pool->freeList[i] = 0;
  }
  return (Balloc)pool;  //return pointer to mem pool struct
}

/*
*requests a block of size bytes from an allocator
*/
extern void *balloc(Balloc pool, unsigned int size){
  struct memoryPool *p = (struct memoryPool*)pool;  //turn pool pointer back to a struct pointer
  
  //requested size is within bounds
  if (size < p->l || size > p->u) {
    return NULL;
  }

  //round reuest size to nearest power of two
  int blockSize = p->l;
  while (blockSize < size) {
    blockSize *= 2;
  }

  //identify the first free block that can satisfy the request
  int blockIndex = -1;
  for (int i = 0; i < p->size / p->l; i++) {
    if (p->freeList[i] == 0 && blockSize == (1 << i)) {
      blockIndex = i;
      break;
    }
  }

  //if theres no block
  if (blockIndex == -1) {
    return NULL;
  }

  //mark the found block 
  p->freeList[blockIndex] = 1;
  for (int i = 0; i < blockIndex; i++) {
    p->freeList[i] = -1;
  }

  //pointer to the start if block in pool
  return &p->memory[blockIndex * blockSize];
}

/*
*deallocates a block of mem
*/
extern void bfree(Balloc pool, void *mem){
  struct memoryPool *p = (struct memoryPool*)pool;
  unsigned char *memVar = (unsigned char*) mem;
  int blockIndex = (memVar - p->memory) / p->l; //index of the block in pool

  //mark block as free
  p->freeList[blockIndex] = 0;
  for (int i = 0; i < blockIndex; i++) {
    if (p->freeList[i] != -1) {
      break;
    }
    p->freeList[i] = 0;
  }
}

/*
*returns the size of an allocation (not a request) lala
*calcualtes the size by findinbg the index of the block in the memory pool
*and using that index to determine the size of the block
*/
extern unsigned int bsize(Balloc pool, void *mem){
  struct memoryPool *p = (struct memoryPool*)pool;
  unsigned char *memVar = (unsigned char*) mem;
  int blockIndex = (memVar - p->memory) / p->l;
  return 1 << blockIndex;   //size of the block, which is equal to the size of the memory pool divided by the number of blocks, and rounded up to the nearest power of 2
}

/*
*writes a textual representaion of an allocator to stdout
*& valuable debugging tool!
*/
extern void bprint(Balloc pool){
  struct memoryPool *p = (struct memoryPool*)pool;
  printf("Memory pool size: %u\n", p->size);
  printf("Lower bound on block size: %d\n", p->l);
  printf("Upper bound on block size: %d\n", p->u);
  printf("Allocated blocks:\n");
  for (int i = 0; i < p->size / p->l; i++) {
    if (p->freeList[i] == 1) {
      printf("%d ", 1 << i);
    }
  }
  printf("\nFree blocks:\n");
  for (int i = 0; i < p->size / p->l; i++) {
    if (p->freeList[i] == 0) {
      printf("%d ", 1 << i);
    }
  }
  printf("\n");
}