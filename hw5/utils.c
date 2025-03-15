//#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <math.h>

#include "utils.h"
#include "error.h"

//returns virual address of a given size
extern void* mmalloc(size_t size){
   void* mapMem=mmap(NULL, size, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE| MAP_ANONYMOUS, -1, 0);
   if(mapMem == MAP_FAILED)
    perror("ERROR: Mmap failed!");

   return mapMem;
}

//size representation for e
extern unsigned int e2size(int e){
   // return pow(2.0, (double)e); (more error prone?)
    return 1 << e;
}

//e representation for size
extern int size2e(unsigned int size){
    return ceil(log(size)/log(2));
}

//sets a bit
extern void bitset(unsigned char *p, int bit){
    unsigned char mask = 1 << bit;
    *p |= mask;
}

//clears a bit
extern void bitclr(unsigned char *p, int bit){
    unsigned char mask = ~(1 << bit);
    *p &= mask;
}

//inverts a bit
extern void bitinv(unsigned char *p, int bit){
    unsigned char mask = 1 << bit;
    *p^=mask;
}

//tests a bit
extern int bittst(unsigned char *p, int bit){
    return (*p >> bit) & (1);
}

//sets the bit to retrieve buddy
extern void *buddyset(void *base, void *mem, int e){
    unsigned long memoryInt = (unsigned long)mem - (unsigned long)base;
    unsigned long mask = 1 << e;
    memoryInt|=mask;
    return base + memoryInt;
}

//clears a bit to retrieve buddy
extern void *buddyclr(void *base, void *mem, int e){
    unsigned long memoryInt = (unsigned long)mem - (unsigned long)base;
    unsigned long mask = ~(1 << e);
    memoryInt&=mask;
    return base + memoryInt;
}

// inverts a bit to retrive left/right buddy
extern void *buddyinv(void *base, void *mem, int e){
    unsigned long memoryInt = (unsigned long)mem - (unsigned long)base;
    unsigned long mask = 1 << e;
    memoryInt^=mask;
    return base + memoryInt;
}

//tests bit of a buddy
extern int buddytst(void *base, void *mem, int e){
    unsigned long memoryInt = (unsigned long)mem - (unsigned long)base;
    memoryInt = (memoryInt >> e) & 1;
    return memoryInt;
}