#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Node* new_node(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

Node* rotate_right(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* rotate_left(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int balance_tree(Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

Node* insert(Node* node, int key) {
    if (node == NULL)
        return (new_node(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = balance_tree(node);
    if (balance > 1 && key < node->left->key)
        return rotate_right(node);

    if (balance < -1 && key > node->right->key)
        return rotate_left(node);

    if (balance > 1 && key > node->left->key) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

Node* min_node(Node* node) {
     Node* current = node;
    while (current->left != NULL)
        current = current->left;

    return current;
}

Node* delete_node(Node* root, int key) {

    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = delete_node(root->left, key);

    else if (key > root->key)
        root->right = delete_node(root->right, key);

    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else 
                *root = *temp; 

            free(temp);
        } else {
            Node* temp = min_node(root->right);


            root->key = temp->key;

            root->right = delete_node(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;


    root->height = 1 + max(height(root->left), height(root->right));


    int balance = balance_tree(root);

    if (balance > 1 && balance_tree(root->left) >= 0)
        return rotate_right(root);

    if (balance > 1 && balance_tree(root->left) < 0) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }

    if (balance < -1 && balance_tree(root->right) <= 0)
        return rotate_left(root);

    if (balance < -1 && balance_tree(root->right) > 0) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    return root;
}