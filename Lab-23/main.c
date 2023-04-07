#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "S:/Git/labs/Lab-23/mytree.h"

#define INF 1e9
#define MAX_STR_LEN 100
#define MAX_NODES 250

TreeNode** current_nodes;
int array_size = 0;

TreeNode* bin_search(int value, int* index)
{
    int left_b = 0, right_b = array_size - 1;
    int pivot;
    TreeNode* current_node;
    int current_v;
    while (left_b <= right_b) {
        pivot = left_b + (right_b - left_b) / 2;
        current_node = current_nodes[pivot];
        current_v = get_value(current_node);
        if (current_v > value) {
            right_b = pivot - 1;
        }
        else if (current_v < value) {
            left_b = pivot + 1;
        }
        else {
            if (index != NULL) {
                *index = pivot;
            }
            return current_node;
        }
    }
    return NULL;
}

void insert_to_array(TreeNode* node)
{
    if (array_size == 0) {
        current_nodes[0] = node;
        array_size++;
        return;
    }
    current_nodes[array_size] = node;
    for (int i = array_size; i > 0; i--) {
        int right_v = get_value(current_nodes[i]);
        int left_v = get_value(current_nodes[i - 1]);
        if (left_v <= right_v) {
            current_nodes[i] = node;
            array_size++;
            return;
        }
        else {
            TreeNode* tmp = current_nodes[i - 1];
            current_nodes[i - 1] = current_nodes[i];
            current_nodes[i] = tmp;
        }
    }
    array_size++;
    return;
}

void clear_array()
{
    free(current_nodes);
    current_nodes = calloc(MAX_NODES, sizeof(TreeNode*));
    array_size = 0;
    return;
}

void rebuild_array(TreeNode* node)
{
    if (node == NULL) {
        return;
    }
    insert_to_array(node);
    TreeNode* first_child = get_child(node, 1);
    TreeNode* next_sibling = get_next_sibling(node, 1);
    if (first_child != NULL) {
        rebuild_array(first_child);
    }
    if (next_sibling != NULL) {
        rebuild_array(next_sibling);
    }
    return;
}

// Interface function prototype for tree constructor1
void tree_builder_ui(Tree* tree);

// Option selection function prototype
void option_handler(char option, Tree* tree);

// Tree deletion interface
void deleting_root_ui(Tree* tree)
{
    printf("Are you sure you want to delete root node? [y/n]\n");
    char option;
    scanf(" %c", &option);

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

TreeNode* get_node_by_value(int value)
{
    TreeNode* result = NULL;
    int found_index;
    result = bin_search(value, &found_index);
    if (result == NULL) {
        printf("There is no node with value %d. Try again: ", value);
        return NULL;
    }
    return result;
}

// Read an integer value from the input stream
void read_value(int* value)
{
    // Remember the return value of scanf
    int input_res = scanf("%d", value);
    while (input_res < 1) { // If a non-number was entered
        printf("Invalid value. Try again: ");
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}; // Clear input buffer
        input_res = scanf("%d", value);
    }
    return;
}

// Function to handle the user interface for building the tree
void tree_builder_ui(Tree* tree)
{
    if (tree == NULL) { // If there is no tree
        clear_array();
        printf("Creating a new tree... Enter root value: ");
        int root_v;
        read_value(&root_v);
        tree = createTree(root_v);
        insert_to_array(get_root(tree));
    }
    // Print the menu of options for the user
    printf("Choose the option:\n");
    printf("\t [1] Add node to the tree\n \
        [2] Remove nodes from the tree\n \
        [3] Find branch with the least depth\n \
        [4] Print tree\n \
        [5] Delete tree\n \
        [q] Quit\n");
    char option;
    scanf(" %c", &option);
    // Call the function to handle selected option
    option_handler(option, tree);
}

// Function to handle the logic for each menu option
void option_handler(char option, Tree* tree)
{
    TreeNode* root = get_root(tree); // Get the root of the tree
    // Switch for each menu option
    switch (option) {
        // ADDING NODE
    case '1':
        // If the root has no children, add a child to it
        if (get_child(root, 1) == NULL) {
            printf("Enter child value you want to add to the root: ");
            int child_v;
            read_value(&child_v);
            while (bin_search(child_v, NULL) != NULL) {
                printf("The new node must be unique. Try a different value: ");
                read_value(&child_v);
            }
            TreeNode* new_node = add_child(root, child_v);
            insert_to_array(new_node);
            printf("Array size is: %d, last elem is: [%d]\n", array_size, current_nodes[array_size - 1]->value);
        }
        // Otherwise, ask the user to enter the path to node and add a child to that node
        else {
            printf("Enter value of the parent node and for the new node.\n");
            printf("For example, '1 4' will add node [4] to the node [1]: ");

            int parent_v;
            int child_v;
            TreeNode* parent = NULL;
            while (parent == NULL) {
                read_value(&parent_v);
                read_value(&child_v);
                parent = get_node_by_value(parent_v);
                while (bin_search(child_v, NULL) != NULL) {
                    printf("The new node must be unique. Try a different value: ");
                    read_value(&child_v);
                }
            }
            TreeNode* new_node = add_child(parent, child_v);
            insert_to_array(new_node);
        }
        // Print the updated tree and return to the main menu
        printf("\nNow tree looks like this:\n");
        printf("<===============>\n");
        print_tree(root, 0);
        printf("<===============>\n");
        tree_builder_ui(tree);
        break;
        // DELETING NODE
    case '2':
        // If the root has no children, ensure that we delete a whole tree
        if (get_child(root, 1) == NULL) {
            deleting_root_ui(tree);
            break;
        }
        printf("Enter node you want to delete: ");
        int child_v;
        read_value(&child_v);
        TreeNode* node;
        while ((node = bin_search(child_v, NULL)) == NULL) {
            printf("This node doesn't exist. Try again: ");
            read_value(&child_v);
        }
        if (node == get_root(tree)) {
            deleting_root_ui(tree);
            break;
        }
        delete_tree_from(tree, node, node);
        clear_array();
        rebuild_array(root);
        // Print the updated tree and return to the main menu
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
        // Calling the min_dfs() to change values of min_len and least_node
        min_dfs(root, 0, &min_len, &least_node);
        printf("The value of the least node is: %d\n", get_value(least_node));
        printf("It's depth is: %d edges\n\n", min_len);
        tree_builder_ui(tree);
        break;
    }
    // PRINTING TREE
    case '4':
        // Print the tree and return to the main menu
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
        // Free the tree
        free_tree(tree);
        free(current_nodes);
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
    //-------------------------------------------------------------//
    printf("===== Welcome to the TreeBuilder48 program =====\n");
    tree_builder_ui(NULL);
    //-------------------------------------------------------------//
    return 0;
}