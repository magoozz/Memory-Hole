#include <string.h>

#include "balloc.h"

static Balloc bp=0;

extern void *malloc(size_t size) {
  bp=bp ? bp : bnew(4096,4,12);
  return balloc(bp,size);
}

extern void free(void *ptr) {
  bfree(bp,ptr);
}

extern void *realloc(void *ptr, size_t size) {
  size_t min(size_t x, size_t y) { return x<y ? x : y; }  //return min size of two values, 
  void *new=malloc(size);
  if (!ptr) //if NULLL return new mem (similar to malloc?)
    return new;
  memcpy(new,ptr,min(size,bsize(bp,ptr)));  //else, copy the mem from pointer into new mem
  free(ptr);  //free ptr
  return new; //new mem
}
