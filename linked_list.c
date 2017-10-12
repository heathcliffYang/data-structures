#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

list_t *list_new() {
    list_t *list;
    MALLOC(list, sizeof(*list));
    list->head = NULL;
    list->size = 0;
    return list;
}

void enqueue(list_t *queue, int data) {
    node_ptr node = node_new(data);
    if (queue->head != NULL)
        node->next = queue->head;
    queue->head = node;
    queue->size += 1;
}

node_t *dequeue(list_t *queue) {
    if (queue->size <= 0)
        return NULL;
    node_ptr node = queue->head;
    queue->size -= 1;
    for (int i = 0; i < queue->size; i++)
        node = node->next;
    if (queue->size <= 0)
        queue->head = NULL;
    return node;
}

node_t *stack_pop(list_t *stack) {
    if (stack->size <= 0)
        return NULL;
    node_ptr node = stack->head;
    stack->size -= 1;
    if (stack->size <= 0)
        stack->head = NULL;
    else
        stack->head = node->next;
    return node;
}

void stack_push(list_t *stack, int data) {
    enqueue(stack, data);
}

void list_print(list_t *list) {
    node_ptr node = list->head;
    for (int i = 0; i < list->size; i++) {
        printf("%d->",node->data);
        node = node->next;
    }
    printf("NULL!\n");
}

node_t *node_new(int data) {
    node_ptr node;
    MALLOC(node, sizeof(*node));
    node->data = data;
    node->next = NULL;
    return node;
}
