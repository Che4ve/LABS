#include <stdio.h>
#include <stdlib.h>

#define INF 1e9

typedef struct TreeNode {
    int value;
    int num_siblings;
    struct TreeNode* first_child;
    struct TreeNode* next_sibling;
} TreeNode;

typedef struct Tree {
    struct TreeNode* root;
} Tree;

TreeNode* create_node(int value)
{
    TreeNode* new_node = malloc(sizeof(TreeNode));
    new_node->value = value;
    new_node->num_siblings = 0;
    new_node->next_sibling = NULL;
    new_node->first_child = NULL;
    return new_node;
}

void add_child(TreeNode* parent, TreeNode* node)
{
    if (parent->first_child == NULL) {
        parent->first_child = node;
    } else {
        TreeNode* space_for_node = parent->first_child;
        while (space_for_node->next_sibling != NULL) {
            space_for_node = space_for_node->next_sibling;
        }
        space_for_node->next_sibling = node;
    }
    node->num_siblings++;
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
    printf("{%d, %d}\n", len, min_len);
    if (node->first_child != NULL) {
        min_len = min_dfs(node->first_child, len + 1, min_len);
    }
    if (node->next_sibling != NULL) {
        min_len = min_dfs(node->next_sibling, len, min_len);
    }
    if (node->first_child == NULL) {
        if (min_len > len) {
            min_len = len;
            printf("least node: %d\n", node->value);
        }
    }
    return min_len;

}



int main() {
    // Create a tree with root node 1
    Tree myTree;
    myTree.root = create_node(1);

    add_child(myTree.root, create_node(2));
    add_child(myTree.root, create_node(3));
    add_child(myTree.root, create_node(6));

    add_child(myTree.root->first_child, create_node(4));
    add_child(myTree.root->first_child, create_node(5));

    add_child(myTree.root->first_child->first_child, create_node(9));

    add_child(myTree.root->first_child->first_child->next_sibling, create_node(10));

    add_child(myTree.root->first_child->next_sibling, create_node(7));

    add_child(myTree.root->first_child->next_sibling->next_sibling, create_node(8));

    print_tree(&myTree);

    printf("MinPath: %d\n", min_dfs(myTree.root, 1, INF));

    return 0;
}