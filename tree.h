#define _TREE_H

typedef struct NODE_TREE node_tree_t;
typedef struct NODE_TREE {
    node_tree_t *left;
    node_tree_t *right;
    int data;
} node_tree_t;

typedef struct TREE {
    node_tree_t *root;
    int size;
} tree_t;

tree_t *new_tree();

void inorder(node_tree_t *tree);
void preorder(node_tree_t *tree);
void postorder(node_tree_t *tree);
void iterInorder(node_tree_t *tree);

/* Heap - priority queue */
/* Max heap is a complete binary tree -> array data structure is suitable */
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

/* Binary search tree */
/* Keys in left subtree are smaller than the key in the root. */
/* Keys in right subtree are larger than the key in the root. */
/* The keys in the tree are 'distinct' -> There is no duplicate keys. */
node_tree_t *binary_search(node_tree_t *root, int key);
node_tree_t *binary_search_iter(node_tree_t *root, int key);
tree_t *binary_search_insert(tree_t *tree, int key);
/* The deleted node is replaced by either the largest pair in its left subtree or the smallest one in its right subtree. */ 
tree_t *binary_search_delete(tree_t *tree, int key);
void *is_binary_search_tree(node_tree_t *root);


node_tree_t *new_tree_node(int data);
