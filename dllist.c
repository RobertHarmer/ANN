#ifndef DLLIST
#define DLLIST

#define null 0

typedef struct dllnode dllnode;
struct dllnode
{
  dllnode* prev;
  dllnode* next;
  int n;
};

void insert(dllnode* list, dllnode* item, int pos)
{
  dllnode* cur = list;

  int i;
  for(i =0; i<pos; i++)
  {
    cur = cur->next;
  }

  if(cur->prev != null)
  {
    cur->prev = item;
    cur->prev->next = item;
    item->prev = cur->prev;
    item->next = cur;
  }

  return;
}


void remove(dllnode* list, dllnode* item, int pos)
{
  dllnode* cur = list;

  int i;
  for(i =0; i<pos; i++)
  {
    cur = cur->next;
  }

  cur->prev->next = cur->next;
  cur->next->prev = cur->prev;

  return;
}

void push(dllnode* list, dllnode* item)
{
  return;
}
#endif
