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
        char* endptr;
        long child_num = strtol(cursor, &endptr, 10);
        while (*endptr == ' ') {
            endptr++;
        }
        if (child_num > get_child_count(parent) || endptr == cursor) {
            printf("incorrect path. Please, try again: ");
            return NULL;
        }
        if (child_num != 0) {
            parent = get_child(parent, child_num);
        }
        cursor = endptr;
    }
    return parent;
}

void read_value(int* value)
{
    int input_res = scanf_s("%d", value);
    while (input_res < 1) {
        printf("Invalid value. Try again: ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}; // ������� ����� �����
        input_res = scanf_s("%d", value);
    }
    return;
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
    char option;
    scanf_s(" %c", &option);
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
            int child_v;
            read_value(&child_v);
            add_child(root, newNode(child_v));
        }
        else {
            printf("Enter path to parent using child numeration.\n");
            printf("For example, the path for\n(root) -> (third child) -> (first child) is '0 3 1'\n");
            printf("Enter path to the parent node: ");
            TreeNode* parent;
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}; // ������� ����� �����
            do {
                char path[MAX_STR_LEN];
                fgets(path, MAX_STR_LEN, stdin);
                parent = get_node_from_path(tree, path);
            } while (parent == NULL);
            printf("Enter child value: ");
            int value;
            read_value(&value);
            add_child(parent, newNode(value));
        }

        printf("\nNow tree looks like this:\n");
        printf("<===============>\n");
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
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}; // ������� ����� �����
        do {
            char path[MAX_STR_LEN];
            fgets(path, MAX_STR_LEN, stdin);
            node = get_node_from_path(tree, path);
        } while (node == NULL);
        if (node == get_root(tree)) {
            deleting_root_ui(tree);
            break;
        }
        delete_tree_from(tree, &node, node);

        printf("\nNow tree looks like this:\n");
        printf("<===============>\n");
        print_tree(root, 0);
        printf("<===============>\n");
        tree_builder_ui(tree);
        break;
        // MIN_DFS
    case '3':
    {
        TreeNode* least_node = root;
        int min_len = INF;
        min_dfs(root, 0, &min_len, &least_node);
        printf("The value of the least node is: %d\n", get_value(least_node));
        printf("It's depth is: %d edges\n\n", min_len);
        tree_builder_ui(tree);
        break;
    }
    // PRINTING TREE
    case '4':
        printf("\n<===============>\n");
        print_tree(root, 0);
        printf("<===============>\n");
        tree_builder_ui(tree);
        break;
        // FREE TREE
    case '5':
        deleting_root_ui(tree);
        break;
        // QUIT
    case 'q':
        free_tree(tree);
        return;
        break;
        // ELSE
    default:
        printf("invalid option.\n");
        tree_builder_ui(tree);
        break;
    }
    return;
}



int main() {

    printf("===== Welcome to the TreeBuilder48 program =====\n");
    tree_builder_ui(NULL);

    return 0;
}