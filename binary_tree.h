#include <stdbool.h>

struct binary_tree{
    int count;
    int (*compare)(void *, void *);
    struct node *root;
};

struct node{
    void* data_ptr;
    struct node* left;
    struct node* right;
};

struct binary_tree* create_binary_tree(int (compare)(void *, void *));

struct binary_tree* insert_binary_tree(struct binary_tree* tree, void* data_ptr);

struct node* insert_node(struct node* node, void* data_ptr, int (*compare)(void *, void *));

bool delete_binary_tree(struct binary_tree* tree, void* data_ptr);

struct node* _delete(struct binary_tree *tree, struct node *node, void *data_ptr, bool *success);

void display_binary_tree(struct node* tree, int level);

int compare_dog_names(void *dog_name_ptr, void *dog_name_ptr2);