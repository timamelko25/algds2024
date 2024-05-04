#ifndef __FUNC_H_
#define __FUNC_H_

typedef struct Node{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
}Node;
 
Node* new_node(int key);
int max(int a, int b);
int height(Node* node);
Node* rotate_right(Node* y);
Node* rotate_left(Node* x);
int balance_tree(Node* node);
Node* insert(Node* node, int key);
Node* min_node(Node* node);
Node* delete_node(Node* root, int key);

#endif