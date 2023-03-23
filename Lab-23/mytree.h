// ЗАГОЛОВОЧНЫЙ ФАЙЛ КАСТОМНОГО ДЕРЕВА
#ifndef __MYTREE_H__
#define __MYTREE_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct _tree_node {
    int value;
    struct _tree_node* first_child;
    struct _tree_node* prev_sibling;
    struct _tree_node* next_sibling;
    struct _tree_node* parent;
} TreeNode;

typedef struct _tree {
    TreeNode* root;
} Tree;

Tree* createTree(int root_value);

TreeNode* newNode(int value);

void add_child(TreeNode* parent, TreeNode* node);

int get_value(TreeNode* node);

TreeNode* get_root(Tree* tree);

TreeNode* get_parent(TreeNode* node);

TreeNode* get_child(TreeNode* parent, int number);

TreeNode* get_next_sibling(TreeNode* node, int number);

TreeNode* get_prev_sibling(TreeNode* node);

void delete_tree_from(TreeNode** node, TreeNode* initial_node);

void free_tree(Tree* tree);

void print_tree(TreeNode* root, int indent);

int min_dfs(TreeNode* node, int len, int min_len);

#endif
