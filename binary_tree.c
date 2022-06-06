#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct binary_tree* create_binary_tree(int (*compare)(void *, void *)){
    struct binary_tree *new_binary_tree = (struct binary_tree *)malloc(sizeof(struct binary_tree));

    if (new_binary_tree){
        new_binary_tree->root = NULL;
        new_binary_tree->compare = compare;
        new_binary_tree->count = 0;
    }
    
    return new_binary_tree;
}

struct binary_tree* insert_binary_tree(struct binary_tree* tree, void* data_ptr){

    struct node *new_node = (struct node *)malloc(sizeof(struct node));

    if (!new_node){
        return NULL;
    }

    new_node->data_ptr = data_ptr;
    new_node->left = NULL;
    new_node->right = NULL;

    if (tree->root == NULL){
        tree->root = new_node;
        tree->count++;
        return tree;
    } else {
        if (tree->compare(data_ptr, tree->root->data_ptr) < 0){
            tree->root->left = insert_node(tree->root->left, data_ptr, tree->compare);
        } else {
            tree->root->right = insert_node(tree->root->right, data_ptr, tree->compare);
        }
    }

    return tree;

}

struct node* insert_node(struct node* node, void* data_ptr, int (*compare)(void *, void *)){

    if (node == NULL){
        struct node *new_node = (struct node *)malloc(sizeof(struct node));

        if (!new_node){
            return NULL;
        }

        new_node->data_ptr = data_ptr;
        new_node->left = NULL;
        new_node->right = NULL;

        return new_node;
    
    } else {

        if (compare(data_ptr, node->data_ptr) < 0){
            node->left = insert_node(node->left, data_ptr, compare);
        } else {
            node->right = insert_node(node->right, data_ptr, compare);
        }

        return node;

    }

}

bool delete_binary_tree(struct binary_tree* tree, void* data_ptr){
    
    // boolean variable to determine whether a node has been deleted successfully from the tree
    bool success;

    struct node *new_node = _delete(tree, tree->root, data_ptr, &success);

    if (success){
        tree->root = new_node;
        tree->count--;

        if (tree->count == 0){
            tree->root = NULL;
        }
    }

    return success;
}

struct node* _delete(struct binary_tree *tree, struct node *node, void *data_ptr, bool *success){
    
    // initialise a set of variables for the process.
    struct node *delete_node;
    struct node *exchange_node;
    struct node *new_root;
    void *hold_ptr;

    if (!node){
        *success = false;
        return NULL;
    }

    if (tree->compare(data_ptr, node->data_ptr) < 0){
        node->left = _delete(tree, node->left, data_ptr, success);
    } else if (tree->compare(data_ptr, node->data_ptr) > 0){
        node->right = _delete(tree, node->right, data_ptr, success);
    } else {
        delete_node = node;

        if (!node->left){
            // deleting a node when the node has no left branch. The right branch is then the new root.
            free(node->data_ptr);
            new_root = node->right;
            free(delete_node);
            *success = true;
            return new_root;
        } else if (!node->right){
            // deleting a node when the node has no right branch. The left branch is then the new root.
            new_root = node->left;
            free(delete_node);
            *success = true;
            return new_root;
        } else {
            // deleting a node when the node has both left and right branches.
            exchange_node = node->left;

            while (exchange_node->right){
                exchange_node = exchange_node->right;
            }

            hold_ptr = node->data_ptr;
            node->data_ptr = exchange_node->data_ptr;
            exchange_node->data_ptr = hold_ptr;

            node->left = _delete(tree, node->left, exchange_node->data_ptr, success);

        }
    }

    return node;

}

void display_binary_tree(struct node* tree, int level){

    // modified the function to in-order traversal. 

    if (tree == NULL){
        return;
    }

    if (tree->right){
        display_binary_tree(tree->right, level + 1);
    }

    for (int i = 0; i < level; i++){
        printf("\t");
    }

    printf("%d. ", level + 1);

    printf("%s\n", (char*)tree->data_ptr);

    // if (tree->left){
    //     display_binary_tree(tree->left, level + 1);
    // }

    if (tree->left){
        display_binary_tree(tree->left, level + 1);
    }

}

int compare_dog_names(void *dog_name_ptr, void *dog_name_ptr2){

    // compare the two dog names
    char *dog_name = (char *)dog_name_ptr;
    char *dog_name2 = (char *)dog_name_ptr2;

    // if the dog names are the same, return 0
    if (strcmp(dog_name, dog_name2) == 0){
        return 0;
    } else if (strcmp(dog_name, dog_name2) < 0){
        return -1;
    } else {
        return 1;
    }

}

int main(){
    struct binary_tree *binary_tree = create_binary_tree(compare_dog_names);

    binary_tree = insert_binary_tree(binary_tree, "Labrador");
    binary_tree = insert_binary_tree(binary_tree, "Rottweiler");
    binary_tree = insert_binary_tree(binary_tree, "Poodle");
    binary_tree = insert_binary_tree(binary_tree, "German Shepherd");
    binary_tree = insert_binary_tree(binary_tree, "Cocker Spaniel");
    binary_tree = insert_binary_tree(binary_tree, "Beagle");
    binary_tree = insert_binary_tree(binary_tree, "Dachshund");
    binary_tree = insert_binary_tree(binary_tree, "Dalmatian");
    binary_tree = insert_binary_tree(binary_tree, "Golden Retreiver");
    binary_tree = insert_binary_tree(binary_tree, "Shetland Sheepdog");

    display_binary_tree(binary_tree->root, 0);

}