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

  clock_t start_t, end_t;
  List list;

  start_t = clock();

  /*
   * Testing Basic list operations
   */
  list = list_new();

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

  /*
   * Testing large list operations
   */
  list = list_new();
  int *data;

  for (int i = 0; i < 1000; i++)
  {
    data = malloc(sizeof(int));
    *data = i;
    list_append(list, data);
  }

  expect_int("list->size", 1000, list->size);
  expect_int("list_at(list, 0)->data", 0, *(int *)list_at(list, 0)->data);
  expect_int("list_at(list, 999)->data", 999, *(int *)list_at(list, 999)->data);

  for (int i = 0; i < 1000; i++)
  {
    data = malloc(sizeof(int));
    *data = i;
    list_prepend(list, data);
  }

  expect_int("list->size", 2000, list->size);
  expect_int("list_at(list, 0)->data", 999, *(int *)list_at(list, 0)->data);
  expect_int("list_at(list, 999)->data", 0, *(int *)list_at(list, 999)->data);
  expect_int("list_at(list, 1000)->data", 0, *(int *)list_at(list, 1000)->data);
  expect_int("list_at(list, 1999)->data", 999, *(int *)list_at(list, 1999)->data);

  for (int i = 0; i < 1000; i++)
  {
    data = malloc(sizeof(int));
    *data = i;
    list_insert(list, data, i);
  }

  expect_int("list->size", 3000, list->size);
  expect_int("list_at(list, 0)->data", 0, *(int *)list_at(list, 0)->data);
  expect_int("list_at(list, 999)->data", 999, *(int *)list_at(list, 999)->data);
  expect_int("list_at(list, 1000)->data", 999, *(int *)list_at(list, 1000)->data);
  expect_int("list_at(list, 1999)->data", 0, *(int *)list_at(list, 1999)->data);
  expect_int("list_at(list, 2000)->data", 0, *(int *)list_at(list, 2000)->data);
  expect_int("list_at(list, 2999)->data", 999, *(int *)list_at(list, 2999)->data);

  list_delete(list, free);

  end_t = clock();

  printf("Passed.\n");
  printf("Time: %ld milliseconds\n", end_t - start_t);
}

void run_tests()
{
  test_list();
}