#ifndef DLLIST
#define DLLIST

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dllist.h"

dllnode* insert(dllnode* list, int item, int pos)
{
  if(list == null)
  {
    dllnode* newList = (dllnode*)malloc(sizeof(dllnode));
    newList->n = item;
    newList->prev = null;
    newList->next = null;
    
    return newList;
  }
  
  dllnode* cur = list;
  dllnode* newNode = (dllnode*)malloc(sizeof(dllnode));
  
  newNode->n = item;

  int i;
  for(i =0; i<pos; i++)
  {
    cur = cur->next;
  }

  if(cur->next == null) // add new node to end of list
  {
    // insert new node at end
    cur->next = newNode;
    newNode->prev = cur;
    newNode->next = null;
  }
  else if(cur->prev == null) // add new node to start of list
  {
    cur->prev = newNode;
    newNode->next = cur;
    newNode->prev = null;
    return newNode;
  }
  else
  {
    cur->prev = newNode;
    newNode->next = cur;
    newNode->prev = cur->prev;
    cur->prev->next = newNode;
  }

  return list;
}


dllnode* removeAt(dllnode* list, int pos)
{
  if(!list)
  {
    return list;
  }
  
  dllnode* cur = list;

  int i;
  for(i =0; i<pos; i++)
  {
    cur = cur->next;
  }

  if(cur->next)
  {
    cur->next->prev = cur->prev;
  }
  else
  {
    cur->prev->next = null;
  }
  if(cur->prev)
  {
    cur->prev->next = cur->next;
  }
  else
  {
    dllnode* newList = cur->next;
    free(cur);
    return newList;
  }
  
  free(cur);

  return list;
}

dllnode* removeItem(dllnode* list, int item)
{
  if(!list)
  {
    printf("list empty\n");
    return list;
  }
  
  dllnode* cur = list;

  while(cur->n != item)
  {
    if(cur->next == null)
    {
      printf("end reached, item not found\n");
      return list;
    }
    cur = cur->next;
  }

  if(cur->next != null)
  {
    cur->next->prev = cur->prev;    
    printf("item not at end\n");
  }
  else
  {
    cur->prev->next = null;
    printf("item at end\n");
  }
  
  if(cur->prev != null)
  {
    cur->prev->next = cur->next;
    printf("item not at beginning\n");
  }
  else
  {
    dllnode* newList = cur->next;
    free(cur);
    printf("item at beginning\n");
    return newList;
  }
  
  free(cur);

  return list;
}


dllnode* push(dllnode* list, int item)
{
  if(list == null)
  {
    dllnode* newList = (dllnode*)malloc(sizeof(dllnode));
    newList->n = item;
    newList->prev = null;
    newList->next = null;
    
    return newList;
  }
  
  dllnode* cur = list;
  
  // go to end of list
  while(cur->next)
  {
    cur = cur->next;
  }
  
  // create new node
  dllnode* newNode = (dllnode*)malloc(sizeof(dllnode));
  
  newNode->n = item;
  
  
  // insert new node at end
  cur->next = newNode;
  newNode->prev = cur;
  newNode->next = null;  
  
  return list;
}

void printdllist(dllnode* list)
{
  dllnode* cur = list;
  
  if(cur == null)
    return;
  
  printf("%d, ",cur->n);
  
  // iterate list
  while(cur->next)
  {
    printf("%d, ",cur->next->n);
    cur = cur->next;
  }
  
  printf("\n");
  
  return;
}
#endif
