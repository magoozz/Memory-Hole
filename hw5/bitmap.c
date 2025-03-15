#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "bitmap.h"
#include "utils.h"

static const int bitsperbyte=8;
/*
* Bitmap searchs from low to high 
* in terms of order.
*/

static int divup(int n, int d) {
  return (n+d-1)/d;
}

//The value found in the bitmap
static int mapsize(unsigned int size, int e) {
  int blocksize=e2size(e);
  int blocks=divup(size,blocksize);
  int buddies=divup(blocks,2);
  return divup(buddies,bitsperbyte);
}

/*
* Computes index to bitmap for wither the of the buddy's addresses
* Right buddy address: convert the left by shifting to the left by one bit
* Left buddy address: given 
*/
static int bitaddr(void *base, void *mem, int e) {
  int addr=buddyclr(base,mem,e)-base;
  int blocksize=e2size(e);
  return addr/blocksize/2;
}

/*
* 1 on bitmap means that one or both buddies is allocated on said level ***
* Creating a new bitmap for a specific exponent & size
*/
extern BitMap bitmapnew(unsigned int size, int e) {
  int ms=mapsize(size,e);
  BitMap b=mmalloc(ms);
  if ((long)b==-1)
    return 0;
  memset(b,0,ms);  //zeros out the entire map
  return b;
}

/*
* Set a specified bit in the map to value of 1
*/
extern void bitmapset(BitMap b, void *base, void *mem, int e) {
  int offset=bitaddr(base,mem,e); //retreive address
  bitset(((unsigned char *)b)+offset/bitsperbyte,offset%bitsperbyte);   //then set the bit to 1
}

/*
* Set a specified bit in the map to value of 0
*/
extern void bitmapclr(BitMap b, void *base, void *mem, int e) {
  int offset=bitaddr(base,mem,e);  //retreive address 
  bitclr(((unsigned char *)b)+offset/bitsperbyte,offset%bitsperbyte);   //then set the bit to 0
}

/*
* Return the specific bit from the bitmap
*/
extern int bitmaptst(BitMap b, void *base, void *mem, int e) {
  int offset=bitaddr(base,mem,e); //retreive address
  return bittst(((unsigned char *)b)+offset/bitsperbyte,offset%bitsperbyte);  //return the bits value
}

extern void bitmapprint(BitMap b, unsigned int size, int e) {
  int ms=mapsize(size,e); //retreive the size of the map
  int byte;
  for (byte=ms-1; byte>=0; byte--)  //each character that is in the 8 bit map
    printf("%02x%s",((unsigned char *)b)[byte],(byte ? " " : "\n"));  //print the two hex digits and either print a space between or after
}
