#include "args/args.h"
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

void run()
{
  Args* args = args_init();

  while (true)
  {
    // Leemos la consola
    args_get(args);

    // Ejemplo de como utilizar el struct

    pid_t childpid;
    int retval;
    int status;

    // printf("PARENT pid: %d\n", getpid());
    childpid = fork();
    // printf("CHILD pid: %d\n", getpid());
    
    if (childpid == 0)
    {
      // execlp(args -> command, args -> command, args->argv[0], NULL);
      if (strcmp(args -> command, "crexec")==0)
      {
        execvp(args -> argv[0], args -> argv);
      }
      exit(123);
    }
    else
    {
      // printf("PARENT waiting for child...\n");
      pid_t exited_child = wait(&status);
      // printf("PARENT: child's exit code: %d\n", WEXITSTATUS(status));
    }


    // printf("Command: %s\n", args->command);
    // printf("Argc:    %i\n", args->argc);
    // printf("Argv:    ");
    // for (size_t i = 0; i < args->argc; i++)
    // {
    //   printf("%s ", args->argv[i]);
    // }
    // printf("\n");
  }

  args_destroy(args);
}

int main()
{
  run();
  return 0;
}
