#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linked_list.h"
#include "tree.h"


int main (int argc, char const *argv[]) {

    printf("argc = %d\n", argc);
    if (argc < 2) {
        printf("1 = queue&stack, 2 = min heap. \n");
        return -1;
    }
    int i =0, j = 0, number = 0;
    srand(time(NULL));
    int type = atoi(argv[1]);
    if (type == 2) {
        /* implementation of min heap */
        printf("implementation of min heap.\n");
        heap_t *heap = new_heap(7);
        for (j = 1; j < heap->max_size; j++)
            printf("%d | ", heap->head[j].key);
        printf("\n");
        for (i = 1; i < heap->max_size; i++) { 
            number = rand()%20;
            printf("Insertion %d: \n", number);
            min_heap_insertion(heap, number);
            for (j = 1; j < heap->max_size; j++) {
                printf("[%d]: ", j);
                printf("%d | ", heap->head[j].key);
            }
            printf("\n");
        }
        for (i = 1; i < heap->max_size; i++) {
            printf("Round %d:\n", i);
            printf("Pop element: %d\n", min_heap_pop(heap)->key);
            for (j = 1; j < heap->max_size; j++)
                printf("%d | ", heap->head[j].key);
            printf("\n");
        }
    }
    else if (type == 1) {
        /* implementation of Queue and Stack */
        list_t *list = list_new();
        printf("Queue\n");
        printf("Enqueue:-----------------------------------\n");
        for (i = 0; i < 10; i++) {
            printf("insert %d\n", i);
            enqueue(list, i);
            list_print(list);
        }
        printf("Dequeue:-----------------------------------\n");
        for (i = 0; i < 10; i++) {
            printf("dequeue : %d\n", dequeue(list)->data);
            list_print(list);
        }
        printf("Stack\n");
        printf("Push:-----------------------------------\n");
        for (i = 0; i < 10; i++) {
            printf("push %d\n", i);
            stack_push(list, i);
            list_print(list);
        }
        printf("Pop:-----------------------------------\n");
        for (i = 0; i < 10; i++) {
            printf("pop : %d\n", stack_pop(list)->data);
            list_print(list);
        }
    }
    else if (type == 3) {
        /* implementation of Binary Search Tree. */
        tree_t *binary_search_tree = new_tree();
        int keys[10]= {};
        node_tree_t *tmp;
        printf("implementation of Binary Search Tree.\n");
        for (i = 0; i < 10; i++) {
            number = rand()%20;
            keys[i] = number;
            printf("Insert: %d\n", keys[i]);
            binary_search_insert(binary_search_tree, number);
            tmp = binary_search_tree->root;
        }
        printf("Insertion complete.\n");
        inorder(binary_search_tree->root);
        printf("\nStart to delete.\n");
        for (i = 0; i < 10; i++) {
            if (binary_search(binary_search_tree->root, keys[i])) {
                binary_search_delete(binary_search_tree, keys[i]);
                printf("Delete - %d\n", keys[i]);
            }
            else
                continue;
            if (binary_search_tree->size > 0)
                is_binary_search_tree(binary_search_tree->root);
        }
        printf("Binary search tree demonstration is done.\n");
    }
    else
        printf("?????????????");
    return 0;
}
