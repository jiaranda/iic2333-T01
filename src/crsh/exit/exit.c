#include "exit.h"
#include <signal.h>


void send_sigint(List* list)
{
  // close every process
  for (int i = 0; i < 255; i++) 
  {
    if (list -> data[i]) 
    {
      pid_t current_pid = list -> data[i] -> pid;
      kill(current_pid, SIGINT);
    }
  }
}

void send_sigkill(List* list)
{
    // kill every process
  for (int i = 0; i < 255; i++) 
  {
    if (list -> data[i]) 
    {
      pid_t current_pid = list -> data[i] -> pid;
      kill(current_pid, SIGKILL);
    }
  }
}