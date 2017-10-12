#define _TREE_H

typedef struct NODE_TREE node_tree_t;
typedef struct NODE_TREE {
    node_tree_t *left;
    node_tree_t *right;
    int data;
} node_tree_t;
 
node_tree_t *new_tree();

void inorder(node_tree_t *tree);
void preorder(node_tree_t *tree);
void postorder(node_tree_t *tree);
void iterInorder(node_tree_t *tree);

/* Heap - priority queue */
/* Max heap is a complete binary tree -> array is suitable */
/* and also a max tree (each node is no smaller than its children) */
/* P230 Programming project */
typedef struct ELEMENT {
    int key;
} element;

typedef struct HEAP {
    int size;
    int max_size;
    element *head;
} heap_t;

heap_t *new_heap(int max_elements);
void min_heap_insertion(heap_t *heap, int n);
element *min_heap_pop(heap_t *heap);
int check_min_heap(heap_t *heap);

node_tree_t *new_tree_node(int data);
