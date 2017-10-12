//#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#define MALLOC(p,s) \
    if (!((p) = malloc(s))) {\
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }

#define IS_EMPTY(first) (!(first))

// self-referential structure
typedef struct list_node *node_ptr;
typedef struct list_node {
    int data;
    node_ptr next;
} node_t;

typedef struct {
    node_ptr head;
    uint32_t size;  /* length of the linked list */
} list_t;

/* FIFO */
list_t *list_new();
void enqueue(list_t *queue, int data);
/* add new node to the queue head*/
node_t *dequeue(list_t *queue);
/* extract the node from queue tail*/

/* stack */
node_t *stack_pop(list_t *stack);
void stack_push(list_t *stack,int data);

void list_print(list_t *list);

node_t *node_new();
