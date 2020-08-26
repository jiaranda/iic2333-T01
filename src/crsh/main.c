#include "args/args.h"
#include <stdio.h>
#include <stdbool.h>

void run()
{
  Args* args = args_init();

  while (true)
  {
    // Leemos la consola
    args_get(args);

    // Ejemplo de como utilizar el struct
    printf("Command: %s\n", args->command);
    printf("Argc:    %i\n", args->argc);
    printf("Argv:    ");
    for (size_t i = 0; i < args->argc; i++)
    {
      printf("%s ", args->argv[i]);
    }
    printf("\n");
  }

  args_destroy(args);
}

int main()
{
  run();
  return 0;
}
