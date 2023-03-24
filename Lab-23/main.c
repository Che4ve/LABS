#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "mytree.h"

#define INF 1e9
#define MAX_STR_LEN 100

void tree_builder_ui(Tree* tree);

void option_selector(char option, Tree* tree);

void deleting_root_ui(Tree* tree)
{
    printf("Are you sure you want to delete root node? [y/n]\n");
    fflush(stdin);
    char option; 
    scanf_s(" %c", &option);
    
    switch (option) {
        case 'y':
            free_tree(tree);
            tree_builder_ui(NULL);
            break;
        case 'n':
            tree_builder_ui(tree);
            break;
        default:
            printf("invalid option.\n");
            tree_builder_ui(tree);
            break;
    }
}

TreeNode* get_node_from_path(Tree* tree, char* path)
{
    TreeNode* root = get_root(tree);
    TreeNode* parent = root;
    char* cursor = path;
    while (cursor < path + strlen(path) - 1) {
        long child_num = strtol(cursor, &cursor, 10);
        if (child_num > get_child_count(parent)) {
            printf("incorrect path. Please, try again\n");
            return NULL;
        }
        while (*cursor == ' ') {
            cursor++;
        }
        if (child_num != 0) {
            parent = get_child(parent, child_num);
        }
    }
    return parent;
}

void tree_builder_ui(Tree* tree)
{
    if (tree == NULL) {
        printf("Creating a new tree... Enter root value: ");
        int root_v; scanf_s("%d", &root_v);
        tree = createTree(root_v);
    }
    printf("Choose the option:\n");
    printf("\t [1] Add node to the tree\n \
        [2] Remove nodes from the tree\n \
        [3] Find branch with the least depth\n \
        [4] Print tree\n \
        [5] Delete tree\n \
        [q] Quit\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}; // flushing stream
    char option; 
    scanf_s(" %c", &option);
    printf("Tree pointer: {%p}", tree);
    option_selector(option, tree);
}

void option_selector(char option, Tree* tree)
{
    TreeNode* root = get_root(tree);
    switch (option) {
        // ADDING NODE
        case '1':
            if (get_child(root, 1) == NULL) {
                printf("Enter child value you want to add to the root: ");
                int child_v; scanf_s("%d", &child_v);
                add_child(root, newNode(child_v));
            } else {
                printf("Enter path to parent using child numeration.\n");
                printf("For example, the path for\n(root) -> (third child) -> (first child) is '0 3 1'\n");
                printf("Enter path to the parent node: ");
                TreeNode* parent;
                do {
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) {}; // flushing stream
                    char path[MAX_STR_LEN];
                    fgets(path, MAX_STR_LEN, stdin);
                    parent = get_node_from_path(tree, path);
                } while ( parent == NULL );
                printf("Enter node value: ");
                int value; scanf_s("%d", &value);
                add_child(parent, newNode(value));
            }
            printf("Now tree looks like this:\n");
            print_tree(root, 0);
            printf("<===============>\n");
            tree_builder_ui(tree);
            break;
        // DELETING NODE
        case '2':
            if (get_child(root, 1) == NULL) {
                deleting_root_ui(tree);
            }
            printf("Enter path to a child you want to delete (recursively).\n");
            printf("Use child numeration.\n");
            printf("For example, the path for\n(root) -> (third child) -> (first child) is '0 3 1'\n");
            printf("Enter path to the parent node: ");
            TreeNode* node;
            do {
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {}; // flushing stream
                char path[MAX_STR_LEN];
                fgets(path, MAX_STR_LEN, stdin);
                node = get_node_from_path(tree, path);
            } while ( node == NULL );
            if (node == get_root(tree)) {
                deleting_root_ui(tree);
                break;
            } 
            TreeNode** p_node = get_real_ref(tree, node);
            printf("pointer to node %p\n", (*p_node));
            delete_tree_from(tree, p_node, *p_node);
            printf("pointer to node %p or %p\n", (*p_node), tree->root->first_child);
            printf("Now tree looks like this:\n");
            print_tree(root, 0);
            printf("<===============>\n");
            tree_builder_ui(tree);
            break;
        // MIN_DFS
        case '3':
        
            break;
        // PRINTING TREE
        case '4':
            printf("<===============>\n");
            print_tree(root, 0);
            printf("<===============>\n");
            tree_builder_ui(tree);
            break;
        // FREE TREE
        case '5':
        
            break;
        // QUIT
        case 'q':
            return;
            break;
        // ELSE
        default:
            printf("invalid option.\n");
            tree_builder_ui(tree);
            break;
    }
}



int main() {
    // Create a tree with root node 1
    printf("===== Welcome to the TreeBuilder48 program =====\n");
    tree_builder_ui(NULL);

    /* Tree* myTree = createTree(1);
    TreeNode* root = get_root(myTree);

    add_child(root, newNode(2));
    add_child(root, newNode(3));
    add_child(root, newNode(6));

    add_child(get_child(root, 1), newNode(4)); // 2 - 4
    add_child(get_child(root, 1), newNode(8)); // 2 - 8

    add_child(get_child(get_child(root, 1), 1), newNode(9)); // 4 - 9

    add_child(get_child(root, 2), newNode(7)); // 3 - 7
    add_child(get_child(root, 2), newNode(5)); // 3 - 5

    //add_child(get_child(root, 3), newNode(10)); // 6 - 10

    //add_child(get_child(get_child(root, 3), 1), newNode(91)); // 4 - 9

    

    printf("Min depth is: %d\n", min_dfs(root, 1, INF));

    TreeNode** second_child = &(root->first_child->next_sibling); // 3
    TreeNode* third_child = get_child(root, 3); // 6

    delete_tree_from(&third_child, third_child); // 3
    
    print_tree(get_root(myTree), 0);
    delete_tree_from(second_child, *second_child); // 3
    //free_tree(myTree);
    printf("-------------\n");
    print_tree(get_root(myTree), 0); */
    return 0;
}