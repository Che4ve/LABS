#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "mytree.h"

#define INF 1e9
#define MAX_STR_LEN 100

void tree_builder_ui(Tree* tree);

void option_selector(char option, Tree* tree);

void tree_builder_ui(Tree* tree)
{
    if (tree == NULL) {
        printf("Welcome to the TreeBuilder48 program!\n");
        printf("Creating a new tree... Enter root value: ");
        int root_v; scanf("%d", &root_v);
        tree = createTree(root_v);
    }
    printf("Choose the option:\n");
    printf("\t [1] Add node to the tree\n \
        [2] Remove nodes from the tree\n \
        [3] Find branch with the least depth\n \
        [4] Print tree\n \
        [5] Delete tree\n \
        [q] Quit\n");
    char option; 
    scanf(" %c", &option);
    option_selector(option, tree);
}

void option_selector(char option, Tree* tree)
{
    TreeNode* root = get_root(tree);
    switch (option) {
        case '1':
            if (get_child(root, 1) == NULL) {
                printf("Enter child value you want to add to the root: ");
                int child_v; scanf("%d", &child_v);
                add_child(root, newNode(child_v));
            } else {
                printf("Enter path to parent using child numeration.\n");
                printf("For example, the path for\n(root) -> (third child) -> (first child) is '0 3 1'\n");
                printf("Enter path to the parent node: ");
                char path[MAX_STR_LEN];
                //fgets(path, MAX_STR_LEN, stdin);
                printf("%s\n", path);
                char* cursor = path;
                TreeNode* parent = root;
                while (cursor != path + strlen(path)) {
                    long child_num = strtol(cursor, &cursor, 0);
                    while (*cursor == ' ') {
                        cursor++;
                    }
                    if (child_num != 0) {
                        parent = get_child(parent, child_num);
                    }
                }
                printf("Enter node value: ");
                int value; scanf("%d", &value);
                add_child(parent, newNode(value));
            }
            printf("Now tree looks like this:\n");
            print_tree(root, 0);
            printf("<===============>\n");
            tree_builder_ui(tree);
            break;
        case '2':

            break;
        case '3':
        
            break;
        case '4':
        
            break;
        case '5':
        
            break;
        case 'q':
            return;
            break;
        default:
            printf("invalid option.\n");
            break;
    }
}

int main() {
    // Create a tree with root node 1

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