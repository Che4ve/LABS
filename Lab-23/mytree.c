#include "S:/Git/labs/Lab-23/mytree.h"

// create a new tree with a single node as the root with the given value
Tree* createTree(int root_value)
{
    // allocate memory for the new tree
    Tree* new_tree = malloc(sizeof(Tree));
    // create a new node with the given value and set it as the root of the new tree
    new_tree->root = newNode(root_value);
    return new_tree;
}

// create a new node with the given value
TreeNode* newNode(int value)
{
    // allocate memory for the new node
    TreeNode* new_node = malloc(sizeof(TreeNode));
    // set the node's value, child count, siblings, parent, and first child to NULL
    new_node->value = value;
    new_node->child_count = 0;
    new_node->prev_sibling = NULL;
    new_node->next_sibling = NULL;
    new_node->first_child = NULL;
    new_node->parent = NULL;
    return new_node;
}

// add a new child node to the parent node
TreeNode* add_child(TreeNode* parent, int value)
{
    TreeNode* node = newNode(value);
    // if the parent node does not have any children, set the new node as its first child
    if (parent->first_child == NULL) {
        parent->first_child = node;
    }
    else {
        // otherwise, find the last sibling of the parent node
        // and set the new node as its next sibling
        TreeNode* last_sibling = parent->first_child;
        while (last_sibling->next_sibling != NULL) {
            last_sibling = last_sibling->next_sibling;
        }
        node->prev_sibling = last_sibling;
        last_sibling->next_sibling = node;
    }
    parent->child_count++;
    node->parent = parent;
    return node;
}

int get_value(TreeNode* node)
{
    return node->value;
}

TreeNode* get_root(Tree* tree)
{
    return tree->root;
}

TreeNode* get_parent(TreeNode* node)
{
    return node->parent;
}

// get the nth child of the given parent node
TreeNode* get_child(TreeNode* parent, int number)
{
    // if the parent node is NULL, return NULL
    if (parent == NULL) {
        return NULL;
    }
    // find the nth child of the parent node and return it
    TreeNode* child = parent->first_child;
    for (int i = 1; i < number; i++) {
        if (child == NULL) {
            break;
        }
        child = child->next_sibling;
    }
    return child;
}

// get the nth sibling node after the given node
TreeNode* get_next_sibling(TreeNode* node, int number)
{
    // if the given node is NULL, return NULL
    if (node == NULL) {
        return NULL;
    }
    // find the nth sibling node after the given node and return it
    TreeNode* sibling = node->next_sibling;
    for (int i = 1; i < number; i++) {
        if (sibling == NULL) {
            break;
        }
        sibling = sibling->next_sibling;
    }
    return sibling;
}

TreeNode* get_prev_sibling(TreeNode* node)
{
    return node->prev_sibling;
}

int get_child_count(TreeNode* node)
{
    return node->child_count;
}

// Returns a reference to the pointer that points to the given node. 
// This is useful for deleting nodes.
TreeNode** get_real_ref(Tree* tree, TreeNode* node)
{
    if (tree == NULL || node == NULL) {
        return NULL;
    }
    if (node == get_root(tree)) {
        return &tree->root;
    }

    TreeNode* parent = get_parent(node);
    TreeNode** p_node = &(parent->first_child);
    while ((*p_node) != NULL) {
        if (*p_node == node) {
            return p_node;
        }
        p_node = &((*p_node)->next_sibling);
    }
    return NULL;
}
// Recursively deletes a tree starting from a given node
void delete_tree_from(Tree* tree, TreeNode* node, TreeNode* initial_node)
{
    if (node->first_child != NULL) {
        delete_tree_from(tree, node->first_child, initial_node);
    }
    if (node->next_sibling != NULL && node != initial_node) {
        delete_tree_from(tree, node->next_sibling, initial_node);
    }
    if (node == initial_node && node->first_child == NULL) {
        // Get siblings
        TreeNode* prev_sibling = node->prev_sibling;
        TreeNode* next_sibling = node->next_sibling;
        TreeNode* parent = node->parent;
        if (parent != NULL) parent->child_count--;
        if (parent != NULL && parent->first_child == node) {
            parent->first_child = next_sibling;
        }
        free(initial_node);
        initial_node = NULL;
        node = NULL;
        if (prev_sibling != NULL) {
            (prev_sibling->next_sibling) = next_sibling;
        }
        if (next_sibling != NULL) {
            next_sibling->prev_sibling = prev_sibling;
        }
    }
    else if (node->first_child == NULL && node->next_sibling == NULL) {
        node->parent->child_count--;
        TreeNode** node_p = get_real_ref(tree, node);
        free(node);
        *node_p = NULL;
    }
    return;
}

// Delete a whole tree
void free_tree(Tree* tree)
{
    TreeNode* root = tree->root;
    delete_tree_from(tree, root, root);
    free(tree);
    tree = NULL;
    return;
}

// Print a tree
void print_tree(TreeNode* root, int indent) {
    if (root == NULL) {
        return;
    }

    for (int i = 0; i < indent; i++) {
        if (i == indent - 1) {
            printf(" |-");
        }
        else {
            printf("   ");
        }
    }
    printf("{%d}\n", root->value);

    TreeNode* child = root->first_child;
    while (child != NULL) {
        print_tree(child, indent + 1);
        child = child->next_sibling;
    }
    return;
}

// Performs a depth-first search on a tree
// and returns the node with the shortest path from the root
void min_dfs(TreeNode* node, int len, int* min_len, TreeNode** least_node)
{
    TreeNode* first_cihld = get_child(node, 1);
    TreeNode* first_sibling = get_next_sibling(node, 1);
    if (first_cihld == NULL) {
        if (*min_len > len) {
            *min_len = len;
            *least_node = node;
        }
    }
    if (first_cihld != NULL) {
        min_dfs(first_cihld, len + 1, min_len, least_node);
    }
    if (first_sibling != NULL) {
        min_dfs(first_sibling, len, min_len, least_node);
    }
}