#include "mytree.h"

#define INF 1e9

Tree* createTree(int root_value)
{
    Tree* new_tree = malloc(sizeof(Tree));
    new_tree->root = newNode(root_value);
    new_tree->depth = 1;
    new_tree->width = 1;
    return new_tree;
}

TreeNode* newNode(int value)
{
    TreeNode* new_node = malloc(sizeof(TreeNode));
    new_node->value = value;
    new_node->children_num = 0;
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
    } else {
        TreeNode* space_for_node = parent->first_child;
        TreeNode* prev_node = space_for_node;
        while (space_for_node->next_sibling != NULL) {
            prev_node = space_for_node;
            space_for_node = space_for_node->next_sibling;
        }
        node->prev_sibling = prev_node;
        space_for_node->next_sibling = node;
    }
    parent->children_num++;
    node->parent = parent;
    return;
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
    if (sibling != NULL) printf("sibl: %d\n", sibling->value);
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

void delete_tree_from(TreeNode** node, TreeNode* initial_node)
{  
    printf("on node (%d)\n", (*node)->value);
    if ((*node) == initial_node) printf("equal\n");
    if ((*node)->first_child != NULL) {
        int next_sib = (*node)->first_child->value;
        delete_tree_from(&(*node)->first_child, initial_node);
        printf("from (%d), back to (%d)\n",next_sib ,(*node)->value);
    }
    if ((*node)->next_sibling != NULL && (*node) != initial_node) {
        int next_sib = (*node)->next_sibling->value;
        delete_tree_from(&(*node)->next_sibling, initial_node);
        printf("from (%d), back to (%d)\n",next_sib ,(*node)->value);
    }
    if ((*node)->first_child == NULL && (*node)->next_sibling == NULL) {
        printf("deleting node [%d]\n", (*node)->value);
        free(*node);
        *node = NULL;
    }
    if ( (*node) == initial_node && (*node)->first_child == NULL ) {
        TreeNode* prev_sibling = (*node)->prev_sibling;
        printf("Init. node - [%p], prev sibling - [%p]\n", (*node), (prev_sibling));
        printf("next sibl is [%p]\n", (*node)->next_sibling);
        if (prev_sibling != NULL) {
            (prev_sibling->next_sibling) = (*node)->next_sibling;
            //(*node)->next_sibling->prev_sibling = prev_sibling;
        }
        //(*node)->next_sibling = NULL;
        //(*node)->prev_sibling = NULL;
        //(*node)->parent = NULL;
        printf("Now [%p] next_sib is [%p]\n", (prev_sibling), (prev_sibling)->next_sibling);
        printf("Now [%p] next_sib is [%p]\n", (*node), (*node)->next_sibling);
        free(*node);
        *node = NULL;
    }
    return;
}

void free_tree(Tree* tree)
{
    TreeNode** p_root = &(tree->root);
    delete_tree_from(p_root, *p_root);
    return;
}

void print_tree(Tree* tree) 
{
    TreeNode* root = tree->root;
    TreeNode* current_node = root->first_child;
    while (current_node != NULL) {
        printf("%d, ", current_node->value);
        current_node = current_node->next_sibling;
    }
    printf("\n");
}

int min_dfs(TreeNode* node, int len, int min_len)
{
    TreeNode* first_cihld = get_child(node, 1);
    TreeNode* first_sibling = get_next_sibling(node, 1);
    printf("{%d, %d}\n", len, min_len);
    if (first_cihld != NULL) {
        min_len = min_dfs(first_cihld, len + 1, min_len);
    }
    if (first_sibling != NULL) {
        min_len = min_dfs(first_sibling, len, min_len);
    }
    if (first_cihld == NULL) {
        if (min_len > len) {
            min_len = len;
            printf("least node: %d\n", node->value);
        }
    }
    return min_len;

}



