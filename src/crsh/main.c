#include "args/args.h"
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "exit/exit.h"

List* pid_list;

void handle_sigint()
{
  printf("sending sigint\n");
  send_sigint(pid_list);
  time_t initial_time = time(NULL);
  while (difftime(time(NULL), initial_time) < 15)
  {
    list_clean(pid_list);
    if(list_empty(pid_list))
    {
      exit(0);
    }
  }
  printf("sending sigkill\n");
  send_sigkill(pid_list);
  printf("free memory\n");
  list_destroy(pid_list);
  exit(0);
}

void run()
{
  Args* args = args_init();
  pid_list = list_init();
  bool continue_program = true;

  while (continue_program == true)
  {
    args_get(args);
    list_clean(pid_list);

    if (strcmp(args -> command, "crexit")==0)
    {
      handle_sigint();
    }
    
    


    pid_t childpid;
    childpid = fork();
    
    
    if (childpid == 0) // child
    {
      // execlp(args -> command, args -> command, args->argv[0], NULL);
      if (strcmp(args -> command, "crexec")==0)
      {
        execvp(args -> argv[0], args -> argv);
        printf("EXEC FAILED: %s\n", strerror(errno));
        exit(0);
      }
      if (strcmp(args -> command, "crlist")==0)
      {
        list_print(pid_list);
        exit(0);
      }
      if (strcmp(args -> command, "crkill")==0)
      {
        pid_t pid_arg = atoi(args->argv[1]);
        int sig = atoi(args->argv[0]);
        if (pid_exists(pid_list, pid_arg))
        {
          kill(pid_arg, sig);
        }
        exit(0);
      }
      exit(0);
    }
    else
    {
      if (strcmp(args -> command, "crexec")==0)
      {
        Process* process = process_init(args -> argv[0], childpid);
        list_add_process(pid_list, process);
      }
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
  signal(SIGINT, handle_sigint);
  run();
  return 0;
}
