#ifndef LIST_H
#define LIST_H

#include "../common.h"

typedef struct _node *Node;
typedef struct _node
{
  void *data;
  Node next;
  Node prev;
} node_struct;

typedef struct _list *List;
typedef struct _list
{
  Node head;
  Node tail;
  int size;
} list_struct;

List list_new();
void list_prepend(List, void *);
void list_append(List, void *);
void list_insert(List, void *, int);
Node list_at(List, int);
void list_remove(List, int, free_fn);
void list_delete(List, free_fn);

#endif // LIST_H