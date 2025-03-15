#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "deq.c"

typedef enum {Head, Tail} End;

typedef enum {PUT, ITH, GET, REM} Breed;

typedef struct TestStep{
    End end;
    Breed type;
    int *data;
}*TestStep;

typedef struct Test{
    TestStep *steps;
    int count;
    char *expected;
}*Test;

//Testing functions
Test createTest(Breed*, End*, int*, char*, int);
char *printInt(Data d);
bool headCheck(char, char);
bool tailCheck(char,char);
bool run();
bool comp(char*, char*);
void freeInt(Data d);
void printReturn(char*, Data);

//head
//put
 bool Put_AddToHeadEmptyList();
 bool Put_AddToHead2Item();   
 //ith
 bool Ith_Head_EmptyList();
 bool Ith_Head_1Item();   
//get
bool Get_Head_EmptyList();
bool Get_Head_1Item();
//rem
bool Rem_Head_EmptyList();
bool Rem_Head_Add1();

//tail
//put
bool Put_AddToTailEmptyList();
bool Put_Add2Tail();
//ith
bool Ith_Tail_EmptyList();
bool Ith_Tail_1Item();
//get
bool Get_Tail_EmptyList();
bool Get_Tail_1Item();
//rem
bool Rem_Tail_EmptyList();
bool Rem_Tail_Add1();

//head + tail
//put
bool Put_Add2Head1Tail();
//get
bool Get_Add2Head2TailGetTail();
bool Get_Add2Tail2HeadGetHead();
//rem
bool Rem_GetHeadTail();
bool Rem_GetTailHead();