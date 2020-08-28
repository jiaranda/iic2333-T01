// code based on
// https://www.learn-c.org/en/Linked_lists

typedef struct node {
    int val;
    struct node * next;
} node_t;

node_t* init_list();

void print_list(node_t * head);

void push(node_t * head, int val);

int pop(node_t ** head);

int remove_last(node_t * head);

int remove_by_index(node_t ** head, int n);