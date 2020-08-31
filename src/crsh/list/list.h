#include <unistd.h>
#include <time.h>

typedef struct process {
  char* name;
  pid_t pid;
  time_t initial_time;
} Process;

typedef struct list {
    int len;
    Process* data[255];
} List;

Process* process_init(char* name, pid_t pid);
List* list_init();
void list_clean(List* list);
void list_data_destroy(List* list);
void list_destroy(List* list);
void list_add_process(List* list, Process* process);
void process_print(Process* process);
void list_print(List* list);