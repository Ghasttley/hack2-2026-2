/*
//
// Created by LENOVO on 14/09/2026.
//

#include <cstdio>
#include <iostream>

class BStree {
   struct Node {
        int key;
        int val;
        Node* left;
        Node* right;
    };

    Node* createNode(int data)
    {
        Node* newNode = new Node();
        newNode->val = data;
        newNode->left = newNode->right = nullptr;
        return newNode;
    }

    Node* root=nullptr;
    public:
    BStree() {
        root = nullptr;
    }

    Node* insertNode(Node* root, int data)
    {
        if (root == nullptr) {
            return createNode(data);
        }
        if (data < root->val) {
            root->left = insertNode(root->left, data);
        }
        else if (data > root->val) {
            root->right = insertNode(root->right, data);
        }
        return root;
    }

    Node* searchNode(Node* root, int key)
    {
        if (root == nullptr || root->val == key) {
            return root;
        }
        return root->val < key ? searchNode(root->right, key): searchNode(root->left, key);
    }


    Node* deleteNode(Node* root, int data)
    {
        if (root == nullptr)
            return root;
        if (data < root->val) {
            root->left = deleteNode(root->left, data);
        }
        else if (data > root->val) {
            root->right = deleteNode(root->right, data);
        }
        else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* temp = minValueNode(root->right);

            root->val = temp->val;

            root->right = deleteNode(root->right, temp->val);
        }
        return root;
    }

    void inorder(Node* root) {
        if (root != nullptr) {
            inorder(root->left);
            printf("%d ", root->val);
            inorder(root->right);
        }
    }

    void preorder(Node* root) {
        if (root != nullptr) {
            printf("%d ", root->val);
            preorder(root->left);
            preorder(root->right);
        }
    }

    void postorder(Node* root) {
        if (root != nullptr) {
            postorder(root->right);
            postorder(root->left);
            printf("%d ", root->val);
        }
    }

};
*/

