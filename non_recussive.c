#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
};

struct stack_node {
    struct node* node;
    struct stack_node* next;
};

struct node* createNode(int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct stack_node* create_stack_node(struct node* node) {
    struct stack_node* newNode = (struct stack_node*)malloc(sizeof(struct stack_node));
    newNode->node = node;
    newNode->next = NULL;
    return newNode;
}

struct Stack {
    struct stack_node* top;
};

struct Stack* create_stack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}
int isStackEmpty(struct Stack* stack) {
    return stack->top == NULL;
}

void push(struct Stack* stack, struct node* node) {
    struct stack_node* newNode = create_stack_node(node);
    newNode->next = stack->top;
    stack->top = newNode;
}

struct node* pop(struct Stack* stack) {
    if (isStackEmpty(stack)) {
        return NULL;
    }
    struct stack_node* temp = stack->top;
    struct node* node = temp->node;
    stack->top = temp->next;
    free(temp);
    return node;
}

void inorder(struct node* root) {
    if (root == NULL) {
        return;
    }

    struct Stack* stack = create_stack();
    struct node* current = root;

    while (current != NULL || !isStackEmpty(stack)) {
        while (current != NULL) {
            push(stack, current);
            current = current->left;
        }
        current = pop(stack);
        printf("%d ", current->data);
        current = current->right;
    }

    free(stack);
}

void preorder(struct node* root) {
    if (root == NULL) {
        return;
    }

    struct Stack* stack = create_stack();
    push(stack, root);

    while (!isStackEmpty(stack)) {
        struct node* current = pop(stack);
        printf("%d ", current->data);
        if (current->right) {
            push(stack, current->right);
        }
        if (current->left) {
            push(stack, current->left);
        }
    }

    free(stack);
}
void postorder(struct node* root) {
    if (root == NULL) {
        return;
    }

    struct Stack* stack1 = create_stack();
    struct Stack* stack2 = create_stack();
    push(stack1, root);

    while (!isStackEmpty(stack1)) {
        struct node* current = pop(stack1);
        push(stack2, current);

        if (current->left) {
            push(stack1, current->left);
        }
        if (current->right) {
            push(stack1, current->right);
        }
    }

    while (!isStackEmpty(stack2)) {
        struct node* current = pop(stack2);
        printf("%d ", current->data);
    }

    free(stack1);
    free(stack2);
}

void insert(struct node** root, int data) {
    struct node* newNode = createNode(data);
    if (*root == NULL) {
        *root = newNode;
    } else {
        struct node* current = *root;
        struct node* parent = NULL;

        while (current != NULL) {
            parent = current;
            if (data < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        if (data < parent->data) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }
}

void freeTree(struct node* root) {
    if (root == NULL) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    struct node* root = NULL;
    int data;
    char choice;

    do {
        printf("Enter an element to insert into the binary tree: ");
        scanf("%d", &data);
        insert(&root, data);

        printf("Do you want to insert another element? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    printf("\nInorder Traversal: ");
    inorder(root);

    printf("\nPreorder Traversal: ");
    preorder(root);

    printf("\nPostorder Traversal: ");
    postorder(root);

    printf("\n");

   
    freeTree(root);

    return 0;
}
