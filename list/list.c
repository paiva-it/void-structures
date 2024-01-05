#include "list.h"

/*
 * Declare helper functions
 */
Node node_new(void *);
void node_delete(Node, free_fn);
void list_add_node(List, Node);
int list_init(List, Node);
void list_empty(List, char *);
void list_index_valid(List, char *, int, int, int);
Node list_at_UNSAFE(List, int);

/*
 * Node Functions
 */

/*
 * Creates a new `Node` with the given data
 */
Node node_new(void *data)
{
  Node node = (Node)malloc(sizeof(node_struct));

  node->data = data;
  node->next = NULL;
  node->prev = NULL;

  return node;
}

/*
 * Deletes the given `Node`
 */
void node_delete(Node node, free_fn free_data)
{
  if (free_data != NULL)
    free_data(node->data);
  free(node);
}

/*
 * List Helper Functions
 */

/*
 * If the `List` is empty, initialize it with the given node
 * Returns `1` if the `List` was empty, `0` otherwise
 */
int list_init(List list, Node node)
{
  if (list->size == 0)
  {
    list->head = node;
    list->tail = node;

    return 1;
  }

  return 0;
}

/*
 * Adds the given `Node` to the list
 */
void list_add_node(List list, Node node)
{
  if (!list_init(list, node))
  {
    node->next = list->head;
    node->prev = list->tail;

    list->head->prev = node;
    list->tail->next = node;
  }

  list->size++;
}

/*
 * Checks if the given `List` is empty,
 */
void list_empty(List list, char *fn_name)
{
  if (list->size == 0)
  {
    fprintf(stderr, "%s: list is empty", fn_name);
    exit(EXIT_FAILURE);
  }
}

/*
 * Checks if the given index is valid
 */
void list_index_valid(List list, char *fn_name, int index, int min, int max)
{
  if (index < min || index > max)
  {
    fprintf(stderr, "%s: invalid index %d", fn_name, index);
    exit(EXIT_FAILURE);
  }
}

/*
 *  List Functions
 */

/*
 * Creates a new `List`
 */
List list_new()
{
  List list = (List)malloc(sizeof(list_struct));

  list->head = NULL;
  list->tail = NULL;
  list->size = 0;

  return list;
}

/*
 * Adds the given data to the end of the `List`
 */
void list_append(List list, void *data)
{
  Node node = node_new(data);

  list_add_node(list, node);

  list->tail = node;
}

/*
 * Adds the given data to the beginning of the `List`
 */
void list_prepend(List list, void *data)
{
  Node node = node_new(data);

  list_add_node(list, node);

  list->head = node;
}

/*
 * Adds the given data to the `List` at the given index
 */
void list_insert(List list, void *data, int index)
{
  list_index_valid(list, "list_insert", index, 0, list->size);

  Node node = node_new(data);

  if (index == 0)
    return list_prepend(list, data);

  if (index == list->size)
    return list_append(list, data);

  Node aux = list_at_UNSAFE(list, index);

  node->next = aux;
  node->prev = aux->prev;

  aux->prev->next = node;
  aux->prev = node;

  list->size++;
}

/*
 * Returns the `Node` at the given index (not protected)
 */
Node list_at_UNSAFE(List list, int index)
{
  if (index == 0 || index == -list->size)
    return list->head;

  if (index == -1 || index == list->size - 1)
    return list->tail;

  if (index < 0)
  {
    Node aux = list->tail;

    for (int i = -1; i > index; i--)
    {
      aux = aux->prev;
    }

    return aux;
  }
  else
  {
    Node aux = list->head;

    for (int i = 0; i < index; i++)
    {
      aux = aux->next;
    }

    return aux;
  }
}

/*
 * Returns the `Node` at the given index
 */
Node list_at(List list, int index)
{
  list_empty(list, "list_at");
  list_index_valid(list, "list_at", index, -list->size, list->size - 1);

  return list_at_UNSAFE(list, index);
}

/*
 * Removes the `Node` at the given index
 */
void list_remove(List list, int index, free_fn free_data)
{
  list_empty(list, "list_remove");
  list_index_valid(list, "list_remove", index, 0, list->size - 1);

  Node aux;

  if (list->size == 1)
  {
    aux = list->head;

    list->head = NULL;
    list->tail = NULL;
  }
  else if (index == 0)
  {
    aux = list->head;

    list->head = list->head->next;
    list->head->prev = list->tail;
    list->tail->next = list->head;
  }
  else if (index == list->size - 1)
  {
    aux = list->tail;

    list->tail = list->tail->prev;
    list->tail->next = list->head;
    list->head->prev = list->tail;
  }
  else
  {
    aux = list_at_UNSAFE(list, index);

    aux->next->prev = aux->prev;
    aux->prev->next = aux->next;
  }

  node_delete(aux, free_data);

  list->size--;
}

/*
 * Deletes the given `List`
 */
void list_delete(List list, free_fn free_data)
{
  list->tail->next = NULL;

  Node aux = list->head;

  while (aux != NULL)
  {
    Node next = aux->next;

    node_delete(aux, free_data);

    aux = next;
  }

  free(list);
}