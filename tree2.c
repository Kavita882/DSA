#include <stdio.h>
#include <stdlib.h>

struct tree {
    int data;
    struct tree *left;
    struct tree *right;
};

typedef struct tree TREE;

// Function declarations
TREE* insert_into_bst(TREE*, int);
void inorder(TREE*);
TREE* delete_from_bst(TREE*, int);
TREE* search(TREE*, int);
TREE* findMin(TREE*);

// Insert into BST
TREE* insert_into_bst(TREE* root, int data) {
    TREE *newnode, *currnode, *parent;

    newnode = (TREE*)malloc(sizeof(TREE));
    newnode->data = data;
    newnode->left = newnode->right = NULL;

    if (root == NULL) {
        printf("Root node inserted\n");
        return newnode;
    }

    currnode = root;
    parent = NULL;

    while (currnode != NULL) {
        parent = currnode;
        if (data < currnode->data)
            currnode = currnode->left;
        else
            currnode = currnode->right;
    }

    if (data < parent->data)
        parent->left = newnode;
    else
        parent->right = newnode;

    printf("Node inserted successfully\n");
    return root;
}

// Traversals
void inorder(TREE* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Search
TREE* search(TREE* root, int key) {
    while (root != NULL) {
        if (key == root->data) {
            printf("Found\n");
            return root;
        }
        else if (key < root->data)
            root = root->left;
        else
            root = root->right;
    }
    printf("Not Found\n");
    return NULL;
}

// Find minimum (used in delete)
TREE* findMin(TREE* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Delete from BST (correct standard method)
TREE* delete_from_bst(TREE* root, int data) {
    if (root == NULL) {
        printf("Item not found\n");
        return root;
    }

    if (data < root->data)
        root->left = delete_from_bst(root->left, data);

    else if (data > root->data)
        root->right = delete_from_bst(root->right, data);

    else {
        // Case 1: No child
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        // Case 2: One child
        else if (root->left == NULL) {
            TREE* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            TREE* temp = root->left;
            free(root);
            return temp;
        }

        // Case 3: Two children
        else {
            TREE* temp = findMin(root->right);
            root->data = temp->data;
            root->right = delete_from_bst(root->right, temp->data);
        }
    }
    return root;
}

// Main function
int main() {
    TREE *root = NULL;
    int choice, data;

    while (1) {
        printf("\n===== MENU =====\n");
        printf("1. Insert\n");
        printf("2. Inorder\n");
        printf("3. Search\n");
        printf("4. Delete\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data: ");
                scanf("%d", &data);
                root = insert_into_bst(root, data);
                break;

            case 2:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;

            case 3:
                printf("Enter value to search: ");
                scanf("%d", &data);
                search(root, data);
                break;

            case 4:
                printf("Enter value to delete: ");
                scanf("%d", &data);
                root = delete_from_bst(root, data);
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }
}
