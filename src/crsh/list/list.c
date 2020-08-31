#include <time.h>
#include "list.h"
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdbool.h>

Process* process_init(char* name, pid_t pid)
{
  Process* process = malloc(sizeof(Process));
  process -> name = malloc(strlen(name) + 1);
  strcpy(process -> name, name);
  process -> pid = pid;
  process -> initial_time = time(NULL);
  return process;
}

void process_destroy(Process* process)
{
  if(!process) return;
  free(process -> name);
  free(process);
}

List* list_init()
{
  List* list = malloc(sizeof(List));
  for (int i = 0; i < 255; i++)
  {
    list -> data[i] = NULL;
  }
  return list;
}

void list_data_destroy(List* list) 
{
  for (int i = 0; i < 255; i++) 
  {
    if (list -> data[i]) 
    {
      process_destroy(list -> data[i]);
    }
  }
}

void list_destroy(List* list) 
{
  if (!list)
  {
    return;
  }
  list_data_destroy(list);
  free(list);
}

void list_clean(List* list)
{
  for (int i = 0; i < 255; i++) 
  {
    if (list -> data[i]) 
    {
      // idea from
      // https://support.sas.com/documentation/onlinedoc/sasc/doc/lr2/waitpid.htm
      int status;
      pid_t pid = list -> data[i] -> pid;
      pid_t endID;
      endID = waitpid(pid, &status, WNOHANG);
      if (endID != 0) // not running
      {
        process_destroy(list -> data[i]);
        list -> data[i] = NULL;
      }
      
    }
  }
}

void list_add_process(List* list, Process* process)
{
  for (int i = 0; i < 255; i++) 
  {
    if (!list -> data[i]) 
    {
      list -> data[i] = process;
      return;
    }
  }
}

void process_print(Process* process)
{
  if (!process) return;
  printf("%d - %s - %f seconds\n", process -> pid, process -> name, difftime(time(NULL), process -> initial_time));
}



void list_print(List* list)
{
  printf("\npid - name - time\n");
  for (int i = 0; i < 255; i++) 
  {
    if (list -> data[i]) 
    {
      process_print(list -> data[i]);
    }
  }
}

bool pid_exists(List* list, pid_t pid)
{
  for (int i = 0; i < 255; i++) 
  {
    if (list -> data[i]) 
    {
      if (list -> data[i] -> pid == pid)
      {
        return true;
      }
    }
  }
  printf("The process with pid %d is not a child of crsh.\n", pid);
  return false;
}

bool list_empty(List* list)
{
  for (int i = 0; i < 255; i++) 
  {
    if (list -> data[i]) 
    {
      return false;
    }
  }
  return true;
}