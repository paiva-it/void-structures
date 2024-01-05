#include "test.h"

void expect_int(char *print, int expected, int received)
{
  if (expected != received)
  {
    fprintf(stderr, "Failed: %s, expected: %d, received: %d", print, expected, received);
    exit(EXIT_FAILURE);
  }
}

void expect_string(char *print, char *expected, char *received)
{
  if (strcmp(expected, received) != 0)
  {
    fprintf(stderr, "Failed: %s, expected: \"%s\", received: \"%s\"", print, expected, received);
    exit(EXIT_FAILURE);
  }
}

void test_list()
{
  printf("Testing List... ");
  List list = list_new();

  list_append(list, "World");
  list_prepend(list, "Hello");

  list_insert(list, "!", 2);

  expect_int("list->size", 3, list->size);
  expect_string("list_at(list, 0)->data", "Hello", (char *)list_at(list, 0)->data);
  expect_string("list_at(list, 1)->data", "World", (char *)list_at(list, 1)->data);
  expect_string("list_at(list, 2)->data", "!", (char *)list_at(list, 2)->data);

  list_remove(list, 1, NULL);

  expect_int("list->size", 2, list->size);
  expect_string("list_at(list, 0)->data", "Hello", (char *)list_at(list, 0)->data);
  expect_string("list_at(list, 1)->data", "!", (char *)list_at(list, 1)->data);

  list_delete(list, NULL);

  printf("Passed.\n");
}

void run_tests()
{
  test_list();
}