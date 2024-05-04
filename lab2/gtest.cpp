#include <stdio.h>
#include <iostream>
#include <gtest\gtest.h>
 
#ifdef __cplusplus
extern "C" {
#endif
 
#include "header.h"
 
#ifdef __cplusplus
}
#endif
 
TEST(testCase, new_node_test)
{
    Node* node = new_node(10);

    EXPECT_EQ(node->key, 10);
    EXPECT_EQ(node->height, 1);

    free(node);
}

TEST(testCase, max_test)
{
    EXPECT_EQ(max(10, 20), 20);
    EXPECT_EQ(max(-5, -10), -5);
    EXPECT_EQ(max(0, 0), 0);
}

TEST(testCase, height_test)
{
    Node* node = new_node(10);
    EXPECT_EQ(height(node), 1);

    node = insert(node, 15);
    EXPECT_EQ(height(node), 2);

    node = insert(node, 20);
    
    EXPECT_EQ(height(node), 2);

    free(node->left);
    free(node->right);
    free(node);
}

TEST(testCase, rotate_right_test)
{
    Node* y = new_node(20);
    y->left = new_node(10);
    y->right = new_node(30);

    Node* result = rotate_right(y);

    EXPECT_EQ(result->key, 10);
    EXPECT_EQ(result->right->key, 20);
    EXPECT_EQ(result->right->right->key, 30);

    free(result->right->right);
    free(result->right);
    free(result->left);
    free(result);
}

TEST(testCase, rotate_left_test)
{
    Node* x = new_node(20);
    x->left = new_node(10);
    x->right = new_node(30);

    Node* result = rotate_left(x);

    EXPECT_EQ(result->key, 30);
    EXPECT_EQ(result->left->key, 20);
    EXPECT_EQ(result->left->left->key, 10);

    free(result->left->left);
    free(result->left);
    free(result->right);
    free(result);
}

TEST(testCase, balance_tree_test)
{
    Node* node = new_node(10);
    node->left = new_node(5);
    node->right = new_node(15);

    EXPECT_EQ(balance_tree(node), 0);

    free(node->left);
    free(node->right);
    free(node);
}

TEST(testCase, insert_test)
{
    Node* root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);

    EXPECT_EQ(root->key, 20);
    EXPECT_EQ(root->left->key, 10);
    EXPECT_EQ(root->right->key, 30);
    EXPECT_EQ(root->right->right->key, 40);
}

TEST(testCase, min_node_test)
{
    Node* root = new_node(20);
    root->left = new_node(10);
    root->right = new_node(30);

    Node* min = min_node(root);

    EXPECT_EQ(min->key, 10);

    free(root->left);
    free(root->right);
    free(root);
}

TEST(testCase, delete_node_node_test)
{
    Node* root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);

    root = delete_node(root, 20);

    EXPECT_EQ(root->key, 30);
    EXPECT_EQ(root->left->key, 10);
    EXPECT_EQ(root->right->key, 40);
}
 
int main(int argc,char**argv)
{
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}