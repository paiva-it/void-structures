#include "common.h"
#include "list/list.h"

void test_list()
{
  List list = list_new();

  list_append(list, "World");
  list_prepend(list, "Hello");

  list_insert(list, "!", 2);

  printf("Size: %d\n", list->size);
  printf("%s %s%s\n", (char *)list_at(list, 0)->data, (char *)list_at(list, 1)->data, (char *)list_at(list, 2)->data);

  list_remove(list, 1, NULL);

  printf("Size: %d\n", list->size);
  printf("%s%s\n", (char *)list_at(list, 0)->data, (char *)list_at(list, 1)->data);

  list_delete(list, NULL);
}

int main()
{
  test_list();

  return 0;
}