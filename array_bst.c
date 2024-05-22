#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
};

struct node* create_node(int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void array_Representation(int tree_array[], int size) {
    printf("Array Representation of Binary Tree:\n");
    for (int i = 0; i < size; i++) {
        if (tree_array[i] != -1) {
            printf("%d ", tree_array[i]);
        } else {
            printf("- ");
        }
    }
    printf("\n");
}

void linked_List_Representation(struct node* root) {
    
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    
    if (root->left != NULL) {
        linked_List_Representation(root->left);
    }

    printf("%d ", root->data);

    if (root->right != NULL) {
        linked_List_Representation(root->right);
    }
}

int main() {
    
    int tree_array[] = {1, 2, 3, 4, 5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    int arraySize = sizeof(tree_array) / sizeof(tree_array[0]);
    array_Representation(tree_array, arraySize);

    
    struct node* root = create_node(1);
    root->left = create_node(2);
    root->right = create_node(3);
    root->left->left = create_node(4);
    root->left->right = create_node(5);
    root->right->left = create_node(6);

    printf("Linked List Representation of Binary Tree: \n");
    linked_List_Representation(root);

    return 0;
}
