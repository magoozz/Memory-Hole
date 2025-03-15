#ifndef UTILS_H
#define UTILS_H

extern void *mmalloc(size_t size);  //wrapper around mmap that takes the same parameters as malloc()

extern unsigned int e2size(int e);  //exponent to size and returns 2^e
extern int size2e(unsigned int size);   //return the log base 2 of size

extern void bitset(unsigned char *p, int bit);
extern void bitclr(unsigned char *p, int bit);
extern void bitinv(unsigned char *p, int bit);
extern int bittst(unsigned char *p, int bit);

extern void *buddyset(void *base, void *mem, int e);
extern void *buddyclr(void *base, void *mem, int e);
extern void *buddyinv(void *base, void *mem, int e);
extern int buddytst(void *base, void *mem, int e);

#endif