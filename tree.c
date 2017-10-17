#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include "linked_list.h"
#include "tree.h"

tree_t *new_tree() {
    tree_t *tree;
    MALLOC(tree, sizeof(*tree));
    tree->root = NULL;
    tree->size = 0;
    return tree;
}

/* binary tree traversals */
void inorder(node_tree_t *tree) {
    if (tree) {
        inorder(tree->left);
        printf("%d - ", tree->data);
        inorder(tree->right);
    }
}

void preorder(node_tree_t *tree) {
    if (tree) {
        printf("%d - ", tree->data);
        preorder(tree->left);
        preorder(tree->right);
    }
}

void postorder(node_tree_t *tree) {
    if (tree) {
        postorder(tree->left);
        postorder(tree->right);
        printf("%d - ", tree->data);
    }
}

void iterInorder(node_tree_t *tree) {
    if (tree) {
        node_tree_t *node = tree;
        list_t *stack = list_new();
        node_ptr tmp;
        for (;;) {
            for (; node; node = node->left)
                stack_push(stack, node->data);
            tmp = stack_pop(stack);
            if (!tmp) break;
            printf("%d - ", tmp->data);
            node = node->right;
        }
    }
}

heap_t *new_heap(int max_elements) {
    element heap_array[max_elements+1];
    for (int i = 0; i < max_elements+1; i++) {
        heap_array[i].key = 0;
    }
    heap_t *heap;
    MALLOC(heap, sizeof(*heap));
    heap->head = heap_array;
    heap->size = 0;
    heap->max_size = max_elements;
    return heap;
}

/* min heap array insertion is from position 1 instead of 0. */
void min_heap_insertion(heap_t *heap, int n) {
    if (heap->size == heap->max_size) {
        fprintf(stderr, "The heap is full.\n");
        exit(EXIT_FAILURE);
    }
    int i = ++(heap->size);
    while ((i!=1) && (n < heap->head[i/2].key)) {
      heap->head[i] = heap->head[i/2];
      i /= 2;
    }
    heap->head[i].key = n;
}

element *min_heap_pop(heap_t *heap) {
    if (heap->size != 0) {
        element *item;
        MALLOC(item, sizeof(*item));
        /* take the smallest element */
        item->key = heap->head[1].key;
        /* use last element to check structure of the min heap */
        element tmp;
        tmp.key = heap->head[heap->size--].key;
        int i = 2, take = 0;
        while (i < heap->size) {
            /* choose smaller one and the direction will be adjusted */
            take = heap->head[i].key > heap->head[i+1].key;
            if (heap->head[i + take].key > tmp.key) break;
            heap->head[i-1] = heap->head[i+take];
            i = 2*(i+take);
        }
        heap->head[i].key = tmp.key;
        return item;
    }
    return NULL;
}

int check_min_heap(heap_t *heap){
    for (int i = 1; i < heap->max_size ; i++) {
        if (heap->head[i].key > heap->head[i*2].key || heap->head[i].key > heap->head[i*2+1].key)
            return -1;
    }
    return 0;
}


/* Binary Search Tree */
node_tree_t *binary_search(node_tree_t *root, int key) {
    /* recursive version */
    if (!root) return NULL;
    if (key == root->data) return root;
    if (key < root->data)
        return binary_search(root->left, key);
    return binary_search(root->right, key);
}

node_tree_t *binary_search_iter(node_tree_t *root, int key) {
    while (root) {
        if (key == root->data) return root;
        if (key < root->data)
            root = root->left;
        else
            root = root->right;
    }
    return NULL;
}

tree_t *binary_search_insert(tree_t *tree, int key) {
    if (tree->size == 0) {
        tree->root = new_tree_node(key);
        printf("Root insertion at %p\n", tree->root);
        tree->root->data = key;
        tree->size += 1;
        return tree;
    }
    node_tree_t *index = tree->root;
    while (index) {
        if (key == index->data) {
            printf("There is already a node with %d in the binary tree.\n", key);
            return tree;
        }
        else if (key < index->data) {
            if (index->left)
                index = index->left;
            else {
                index->left = new_tree_node(key);
                break;
            }
        }
        else if (key > index->data) {
            if (index->right)
                index = index->right;
            else {
                index->right = new_tree_node(key);
                break;
            }
        }
    }
    tree->size += 1;
    return tree;
}

tree_t *binary_search_delete(tree_t *tree, int key) {
    node_tree_t *index = tree->root;
    node_tree_t *previous = index;
    int i = 0;
    while (index) {
        if (key == index->data) {
            if (index == tree->root) {
                if (index->right != NULL)
                    tree->root = index->right;
                else {
                    tree->root = index->left;
                    tree->size -= 1;
                    printf("Doneeeeeeeeeeeeeeeeeeeeeee, %d \n", tree->size);
                    return tree;
                }
                index = index->right;
                previous = tree->root;
            }
            if (i == 0) {
                if (index->right != NULL)
                    previous->left = index->right;
                else {
                    previous->left = index->left;
                    tree->size -= 1;
                    return tree;
                }
                previous = previous->left;
            }
            else {
                if (index->right != NULL)
                    previous->right = index->right;
                else {
                    previous->right = index->left;
                    tree->size -= 1;
                    return tree;
                }
                previous = previous->right;
            }
            index = index->right;
            while (index) {
                if (index->right != NULL)
                    previous->right = index->right;
                else {
                    previous->right = index->left;
                    tree->size -= 1;
                    return tree;
                }
                previous = previous->right;
                index = index->right;
            }
            tree->size -= 1;
            return tree;
        }
        else
            previous = index;
        if (key < index->data) {
            i = 0;
            index = index->left;
        }
        else if (key > index->data) {
            i = 1;
            index = index->right;
        }
    }
    return NULL;
}

void *is_binary_search_tree(node_tree_t *index) {
    if (index->left != NULL) {
        if (index->data > index->left->data)
            is_binary_search_tree(index->left);
        else {
            fprintf(stderr, "This is not binary search tree.(left)\n");
            exit(EXIT_FAILURE);
        }
    }
    if (index->right != NULL) {
        if (index->data < index->right->data)
            is_binary_search_tree(index->right);
        else {
            fprintf(stderr, "This is not binary search tree.(right)\n");
            exit(EXIT_FAILURE);
        }
    }
    printf("!!!!!!!!!!\n");
}

node_tree_t *new_tree_node(int data) {
    node_tree_t *node;
    MALLOC(node, sizeof(*node));
    node->left = NULL;
    node->right = NULL;
    node->data = data;
    return node;
}

