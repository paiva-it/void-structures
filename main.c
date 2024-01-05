#include "common.h"
#include "list/list.h"
#include "test/test.h"

int main(int argc, char *argv[])
{
  if (argc == 2)
  {
    if (strcmp(argv[1], "test") == 0)
    {
      run_tests();
    }
  }

  return 0;
}