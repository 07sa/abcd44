#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
};

struct node* create_node(int val) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct node* insert(struct node* root, int val) {
    if (root == NULL) {
        return create_node(val);
    }
    if (val < root->data) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    return root;
}

int height(struct node* root) {
    if (root == NULL) {
        return -1;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int count_nodes(struct node* root) {
    if (root == NULL) {
        return 0;
    }
    return count_nodes(root->left) + count_nodes(root->right) + 1;
}

int count_leaf_nodes(struct node* root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    return count_leaf_nodes(root->left) + count_leaf_nodes(root->right);
}

int findMin(struct node* root) {
    if (root == NULL) {
        printf("Error: Tree is empty\n");
        return -1; 
    }
    while (root->left != NULL) {
        root = root->left;
    }
    return root->data;
}

int findMax(struct node* root) {
    if (root == NULL) {
        printf("Error: Tree is empty\n");
        return -1; 
    }
    while (root->right != NULL) {
        root = root->right;
    }
    return root->data;
}

void printLeaf_nodes(struct node* root) {
    if (root == NULL) {
        return;
    }
    if (root->left == NULL && root->right == NULL) {
        printf("%d ", root->data);
    }
    printLeaf_nodes(root->left);
    printLeaf_nodes(root->right);
}

void printLevel_Wise(struct node* root) {
    if (root == NULL) {
        return;
    }
    struct node* queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        struct node* currNode = queue[front++];
        printf("%d ", currNode->data);

        if (currNode->left != NULL) {
            queue[rear++] = currNode->left;
        }
        if (currNode->right != NULL) {
            queue[rear++] = currNode->right;
        }
    }
}

void delete_tree(struct node* root) {
    if (root == NULL) {
        return;
    }
    delete_tree(root->left);
    delete_tree(root->right);
    free(root);
}

int main() {
    struct node* root = NULL;

    int n;
    printf("Enter the number of elements to insert: ");
    scanf("%d", &n);
    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        int element;
        scanf("%d", &element);
        root = insert(root, element);
    }

    int h = height(root);
    printf("Height of the BST: %d\n", h);

    int numNodes = count_nodes(root);
    printf("Number of nodes in the BST: %d\n", numNodes);

    int numLeafNodes = count_leaf_nodes(root);
    printf("Number of leaf nodes in the BST: %d\n", numLeafNodes);

    int minNode = findMin(root);
    int maxNode = findMax(root);
    printf("Minimum node value: %d\n", minNode);
    printf("Maximum node value: %d\n", maxNode);

    printf("Leaf nodes of the BST: ");
    printLeaf_nodes(root);
    printf("\n");

    printf("Nodes of the BST level-wise: ");
    printLevel_Wise(root);
    printf("\n");

    delete_tree(root);

    return 0;
}
