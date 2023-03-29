#include "mytree.h"

#define INF 1e9

Tree* createTree(int root_value)
{
    Tree* new_tree = malloc(sizeof(Tree));
    new_tree->root = newNode(root_value);
    return new_tree;
}

TreeNode* newNode(int value)
{
    TreeNode* new_node = malloc(sizeof(TreeNode));
    new_node->value = value;
    new_node->child_count = 0;
    new_node->prev_sibling = NULL;
    new_node->next_sibling = NULL;
    new_node->first_child = NULL;
    new_node->parent = NULL;
    return new_node;
}

void add_child(TreeNode* parent, TreeNode* node)
{
    if (parent->first_child == NULL) {
        parent->first_child = node;
    }
    else {
        TreeNode* last_sibling = parent->first_child;
        while (last_sibling->next_sibling != NULL) {
            last_sibling = last_sibling->next_sibling;
        }
        node->prev_sibling = last_sibling;
        last_sibling->next_sibling = node;
    }
    parent->child_count++;
    node->parent = parent;
    return;
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

TreeNode* get_child(TreeNode* parent, int number)
{
    if (parent == NULL) {
        return NULL;
    }
    TreeNode* child = parent->first_child;
    for (int i = 1; i < number; i++) {
        if (child == NULL) {
            break;
        }
        child = child->next_sibling;
    }
    return child;
}

TreeNode* get_next_sibling(TreeNode* node, int number)
{
    if (node == NULL) {
        return NULL;
    }
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

TreeNode** get_real_ref(Tree* tree, TreeNode* node)
{
    if (tree == NULL || node == NULL) {
        return NULL;
    }
    if (node == get_root(tree)) {
        return &tree->root;;
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

void delete_tree_from(Tree* tree, TreeNode** node, TreeNode* initial_node)
{
    if ((*node)->first_child != NULL) {
        delete_tree_from(tree, &((*node)->first_child), initial_node);
    }
    if ((*node)->next_sibling != NULL && (*node) != initial_node) {
        delete_tree_from(tree, &((*node)->next_sibling), initial_node);
    }
    if ((*node) == initial_node && (*node)->first_child == NULL) {
        TreeNode* prev_sibling = (*node)->prev_sibling;
        TreeNode* next_sibling = (*node)->next_sibling;
        node = get_real_ref(tree, *node);
        if (get_parent(*node) != NULL) (*node)->parent->child_count--;
        if (prev_sibling != NULL) {
            (prev_sibling->next_sibling) = next_sibling;
        }
        if (next_sibling != NULL) {
            TreeNode* parent = (*node)->parent;
            next_sibling->prev_sibling = prev_sibling;
            parent->first_child = next_sibling;
        }
        else {
            *node = NULL;
        }
        free(initial_node);
        initial_node = NULL;
    }
    else if ((*node)->first_child == NULL && (*node)->next_sibling == NULL) {
        (*node)->parent->child_count--;
        free(*node);
        *node = NULL;
    }
    return;
}

void free_tree(Tree* tree)
{
    TreeNode** p_root = &(tree->root);
    delete_tree_from(tree, p_root, *p_root);
    free(tree);
    tree = NULL;
    return;
}

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