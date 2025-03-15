#ifndef FREELIST_H
#define FREELIST_H

typedef void *FreeList;

extern FreeList freelistnew(unsigned int size, void *base, int l, int u);   

extern void *freelistalloc(FreeList f, void *base, int e, int l, int u);    //maintain free blocks while removing an element from the list & returning the address
extern void freelistfree(FreeList f, void *base, void *mem, int e, int l);  //free a freelist element given the address
extern int freelistsize(FreeList f, void *base, void *mem, int l, int u);   //check if a given free list exists, if so return the size

extern void freelistprint(FreeList f, unsigned int size, int l, int u);     //
extern void printNode (void *node);
static void updateHead(FreeList f, void* mem, int index);
static void split(FreeList f, void *base, void* mem, int i, int deltaE, int u, int l);
static void splitToLevel(FreeList f, void *base, void* mem, int sLevel, int currLevel,int offset);



#endif
