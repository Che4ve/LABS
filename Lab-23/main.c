#include <stdio.h>
#include <stdlib.h>
#include "mytree.h"

#define INF 1e9



int main() {
    // Create a tree with root node 1
    Tree* myTree = createTree(1);
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
    printf("2 [%p] sibling is %p\n",(root->first_child), *second_child);
    delete_tree_from(second_child, root->first_child->next_sibling); // 3
    printf("-------------\n");
    printf("2 sibling is %p\n", root->first_child->next_sibling);
    print_tree(myTree);
    free_tree(myTree);
    //print_tree(myTree);
    return 0;
}