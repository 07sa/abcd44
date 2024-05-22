#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

struct node *create_node(int data){
    struct node *n;
    n = (struct node *)malloc(sizeof(struct node));
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    return n;
}

int isBST(struct node *root){
    static struct node *prev = NULL;
    if (root != NULL)
    {
        if (!isBST(root->left))
        {
            return 0;
        }
        if (prev != NULL && root->data <= prev->data)
        {
            return 0;
        }
        prev = root;
        return isBST(root->right);
    }
    else
    {
        return 1;
    }
}


struct node *recursive_binary_search(struct node *root, int key){
    if (root==NULL)
    {
        return NULL;
    }
    if (root->data ==key)
    {
        return root;
    }
    else if (root->data > key)
    {
        return recursive_binary_search(root->left, key);
    }
    else
    {
        return recursive_binary_search(root->right, key);
    }
}

struct node *iterative_binary_search(struct node *root, int key){
    while (root != NULL)
    {
        if (root->data == key)
        {
            return root;
        }
        else if (key < root->data)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
        return NULL; 
    }
}

struct node* insert_bst(struct node* root, int key) {
    if (root == NULL) {
        return create_node(key);
    }

    struct node* prev = NULL;
    struct node* current = root;

    while (current != NULL) {
        prev = current;

        if (key == current->data) {
            printf("Cannot insert..\n");
            return root;
        } else if (key < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    struct node* new_node = create_node(key);
    if (key < prev->data) {
        prev->left = new_node;
    } else {
        prev->right = new_node;
    }

    return root;
}

////inoreder predecessor - left subtree ka right most element
struct node *inorder_presecessor(struct node *root){
    root = root->left;
    while (root->right != NULL)
    {
        root = root->right;
    }
    return root;  
}

struct node *delete_node(struct node *root, int value){
    struct node *ipre;
    //// base case
    if (root == NULL)
    {
        return NULL;
    }
    if (root->left == NULL && root->right == NULL)
    {
        free(root);
        return NULL;
    }
    
    
    ////search the node
    if (value < root->data)
    {
        root->left = delete_node(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = delete_node(root->right, value);
    }
    else
    {
        ipre = inorder_presecessor(root);
        root->data = ipre->data;
        root->left = delete_node(root->left, ipre->data);
    }
}

void inorder(struct node *root){
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ",root->data);
        inorder(root->right);
    }
}


 

int main(){
    struct node *root = NULL;
    int choice, data;

    while (1)
    {
        printf("\n1. Insert\n2. Delete\n3. Search\n4. Inorder Traversal\n5. Exit\n");
        printf("Enter your choice :");
        scanf("%d",&choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &data);
            root = insert_bst(root, data);
            break;
        case 2:
            printf("Enter value to delete: ");
            scanf("%d",&data);
            root = delete_node(root,data);
            break;
        case 3:
            printf("Enter value to search: ");
            scanf("%d", &data);
            if (iterative_binary_search(root, data) != NULL) {
                printf("Value found in the tree.\n");
                } else {
                    printf("Value not found in the tree.\n");
                    }
            break;
        case 4:
            printf("Inorder Traversal: ");
            inorder(root);
            break;
        case 5:
            exit(0);
            break;
        
        default:
            printf("Invalid choice.\n");
        }
    }
    return 0;
}