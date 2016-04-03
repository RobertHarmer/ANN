#ifndef DLLIST_H
#define DLLIST_H

#define null 0


typedef struct dllnode dllnode;
struct dllnode
{
  dllnode* prev;
  dllnode* next;
  int n;
};


dllnode* insert(dllnode* list, int item, int pos);
dllnode* removeAt(dllnode* list, int pos);
dllnode* removeItem(dllnode* list, int item);
dllnode* push(dllnode* list, int item);
void printdllist(dllnode* list);

#endif
