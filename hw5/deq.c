#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deq.h"
#include "error.h"

// indices and size of array of node pointers
typedef enum {Head,Tail,Ends} End;  //head = previous & tail = next

typedef struct Node {
  struct Node *np[Ends];		// next/prev neighbors, array of two pointers
  Data data;
} *Node;

typedef struct {
  Node ht[Ends];			// head/tail nodes of entire list
  int len;
} *Rep;

static Rep rep(Deq q) {     //given queue translats into data strucher that gives head,tail,&length
  if (!q) ERROR("zero pointer");
  return (Rep)q;
}

//TODO: appened onto an end, len++
static void put(Rep r, End e, Data d) {
  Node new = (Node) malloc(sizeof(struct Node));    //allocate the new node
  memset(new,0,sizeof(struct Node));
  new -> data = d;    //set new data as what the new node is
  if (!new) ERROR("malloc() failed to initiate");   //send error message if relevant
  if (r -> len == 0) {    //set node pointer to head and tail if length equals 0
    r -> ht[Head] = new;
    r -> ht[Tail] = new;
  } else {    //find the current head (len++)
      Node temp = r -> ht[e];   //storing
      r -> ht[e] = new;     //set either head or tail
      if (e != Head) {      //tail
        new -> np[Head] = temp;
        temp -> np[Tail] = new;
      } else {        //head
        new -> np[Tail] = temp;  //new's next = temp 
        temp -> np[Head] = new;  //temp's previous = new
      }
  }
  r -> len++;      //increase length
}

//TODO: return by 0-base index, len unchnaged
// return a specific numbered element get the head, head's next, and next's next until you reach the ith element
// error on negative number
static Data ith(Rep r, End e, int i)  { 
  Node temp = r -> ht[e];   //storing the element to start the index at
  int tailNum = r -> len - 1;
  if (r -> len == 0) {
    ERROR("There is nothing in the list to ith.");
    return 0;
  }

  if (i < 0 || i > tailNum) {
    ERROR("%d is an invalid index (should be: 0 <= index < %d)", i, tailNum);
    return 0;
  }
  
  if (e != Head) { //tail
    int count = tailNum;
    while(count > i) {
      temp = temp -> np[Head];
      count --;
    }
  } else { //head
    int count = 0;
    while(count < i) {
      temp = temp -> np[Tail];
      count++;
    }
  }

  Data temptemp = temp -> data;
  return temptemp;
  }

//TODO: return from an end, len--
//remove either head or tail
//turn the previous of that tail to the new tail
//or turn the next of that head into the new head
static Data get(Rep r, End e)         { 
  if (r -> len == 0) {    //sif the list is empty there can be no put
    ERROR("There is nothing in list to get.");
  }
  Node temp = r -> ht[e];   //storing the head or tail to be deleted
    if (e != Head) {      //tail    ??????
      Node newTail = temp -> np[Head];
      r -> ht[e] = newTail; 
      newTail -> np[Tail] = 0;   //set tails previous to null
    } else {    //head
      Node newHead = temp -> np[Tail];
      r -> ht[e] = newHead;
      newHead -> np[Head] = 0;   //set heads next to null
    }
  r -> len--;      //decrease length
  Data temptemp = temp -> data; //save temp's data to return before freeing it
  free(temp);
  return temptemp;
  }
   

//TODO: return by == comparing, len-- (if found)
// get but a specific element value
//new head or tail
//in the middle, get the previous and next of that item before deleting it
static Data rem(Rep r, End e, Data d) { 
  int tailNum = r -> len - 1;
  Node temp = r -> ht[e];   //storing the element to start the index atee
  int flag = 0;

  if (r -> len == 0) {
    ERROR("There is nothing in the list to rem.");
    return 0;
  } 
  
  if (e != Head) { //tail
    int count = tailNum;
    while(count >= 0) {
      Data t = temp -> data;
      if ((strcmp((char *) t,(char *) d))== 0) {
        if ((int) temp == (int) (r -> ht[Tail])) {
          Node newTail = temp -> np[Head];
          r -> ht[Tail] = newTail; 
          newTail -> np[Tail] = 0;   //set tails next to null
        } else if((int) temp == (int) (r -> ht[Head])) {
            Node newHead = temp -> np[Tail];
            r -> ht[Head] = newHead;
            newHead -> np[Head] = 0;   //set heads previous to null
        } else {
           Node newP = temp -> np[Head];  //previous to assign to next LEFT
           Node newN = temp -> np[Tail];  //next to assign to previous RIGHT
           newN -> np[Head] = newP;
           newP -> np[Tail] = newN;
        }
        flag = 1;
        break;
      }
      temp = temp -> np[Head];
      count --;
    } 
  } else { //head
    int count = 0;
    while(count <= tailNum) {
      Data t = temp -> data;
      if ((strcmp((char *) t,(char *) d))== 0) {
        if ((int) temp == (int) (r -> ht[Head])) {
          Node newHead = temp -> np[Tail];
          r -> ht[Head] = newHead;
          newHead -> np[Head] = 0;   //set heads previous to null
        } else if ((int) temp == (int) (r -> ht[Tail])) {
            Node newTail = temp -> np[Head];
            r -> ht[Tail] = newTail; 
            newTail -> np[Tail] = 0;   //set tails next to null
        } else {
           Node newP = temp -> np[Head];  //previous to assign to next LEFT
           Node newN = temp -> np[Tail];  //next to assign to previous RIGHT
           newN -> np[Head] = newP;
           newP -> np[Tail] = newN;
        }
        flag = 1;
        break;
      }

      temp = temp -> np[Tail];
      count ++;
    }
  }
  if (flag == 1) {
      r -> len--;      //decrease length
  } else {
    ERROR("This item does not exist.");
    return 0;
  }
  Data temptemp = temp -> data;
  free(temp);
  return temptemp;
  }

extern Deq deq_new() {
  Rep r=(Rep)malloc(sizeof(*r));
  if (!r) ERROR("malloc() failed");
  r->ht[Head]=0;
  r->ht[Tail]=0;
  r->len=0;
  return r;
}

extern int deq_len(Deq q) { return rep(q)->len; }

extern void deq_head_put(Deq q, Data d) {        put(rep(q),Head,d); }
extern Data deq_head_get(Deq q)         { return get(rep(q),Head); }
extern Data deq_head_ith(Deq q, int i)  { return ith(rep(q),Head,i); }
extern Data deq_head_rem(Deq q, Data d) { return rem(rep(q),Head,d); }

extern void deq_tail_put(Deq q, Data d) {        put(rep(q),Tail,d); }
extern Data deq_tail_get(Deq q)         { return get(rep(q),Tail); }
extern Data deq_tail_ith(Deq q, int i)  { return ith(rep(q),Tail,i); }
extern Data deq_tail_rem(Deq q, Data d) { return rem(rep(q),Tail,d); }

extern void deq_map(Deq q, DeqMapF f) {
  for (Node n=rep(q)->ht[Head]; n; n=n->np[Tail])
    f(n->data);
}

extern void deq_del(Deq q, DeqMapF f) {
  if (f) deq_map(q,f);
  Node curr=rep(q)->ht[Head];
  while (curr) {
    Node next=curr->np[Tail];
    free(curr);
    curr=next;
  }
  free(q);
}

extern Str deq_str(Deq q, DeqStrF f) { //ith & rem use similar forloop
  char *s=strdup("");
  for (Node n=rep(q)->ht[Head]; n; n=n->np[Tail]) {   //loop starts at head and keeps getting next till n becomes null
    char *d=f ? f(n->data) : n->data; //if f is null it prints n data
    char *t; asprintf(&t,"%s%s%s",s,(*s ? " " : ""),d);
    free(s); s=t;
    if (f) free(d);
  }
  return s;
}
