// CUSTOM TREE HEADER FILE
#ifndef MYTREE_H
#define MYTREE_H

#include <stdio.h>
#include <stdlib.h>
//#define NULL ((char *)0)

// Tree node structure
typedef struct _tree_node {
    int value;
    int child_count;
    struct _tree_node* first_child;
    struct _tree_node* prev_sibling;
    struct _tree_node* next_sibling;
    struct _tree_node* parent;
} TreeNode;

// Tree structure
typedef struct _tree {
    TreeNode* root;
} Tree;

// Create a new tree
Tree* createTree(int root_value);

// Initialize a new node
TreeNode* newNode(int value);

// Add a child node
TreeNode* add_child(TreeNode* parent, int value);

// Get node value
int get_value(TreeNode* node);

// Get the root of the tree
TreeNode* get_root(Tree* tree);

// Get parent node
TreeNode* get_parent(TreeNode* node);

// Get child node (by number)
TreeNode* get_child(TreeNode* parent, int number);

// Get adjacent node (by number)
TreeNode* get_next_sibling(TreeNode* node, int number);

// Get previous adjacent node
TreeNode* get_prev_sibling(TreeNode* node);

// Get the number of child nodes
int get_child_count(TreeNode* node);

// Get the original pointer to the node
TreeNode** get_real_ref(Tree* tree, TreeNode* node);

// Delete part of the tree starting from the node
void delete_tree_from(Tree* tree, TreeNode* node, TreeNode* initial_node);

// Delete the entire tree
void free_tree(Tree* tree);

// Print the tree on the screen
void print_tree(TreeNode* root, int indent);

// Search for the tree leaf with the minimum depth
void min_dfs(TreeNode* node, int len, int* min_len, TreeNode** least_node);

TreeNode* dfs(TreeNode* node, int value);

#endif