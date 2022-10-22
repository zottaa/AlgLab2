//
// Created by sasha on 19.10.2022.
//

#ifndef ALGLAB2_BINARYSEARCHTREE_H
#define ALGLAB2_BINARYSEARCHTREE_H

#include <stack>

template<class K, class T>
class BinarySearchTree {
public:
    struct Node;
private:
    Node *root{};
    int _size;

public:
    struct Node {
        Node *left;
        Node *right;
        K key;
        T value;

        Node(K key, T value) {
            this->left = nullptr;
            this->right = nullptr;
            this->key = key;
            this->value = value;
        }
    };

    BinarySearchTree() {
        root = nullptr;
        _size = 0;
    }

    BinarySearchTree(K key, T value) {
        root = new Node(Node(key, value));
        _size = 0;
    }

    ~BinarySearchTree() {
        delete root;
    }

    T &search(K key) {
        Node *temp = root;
        while (temp != nullptr && key != temp->key) {
            if (key < temp->key) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }
        try {
            if (temp == nullptr)
                throw std::exception();
            return temp->value;
        } catch (std::exception& e) {
            std::cout << "Exception!\n";
        }
    }

    bool add(K key, T value) {
        if (root == nullptr) {
            root = new Node(Node(key, value));
            _size++;
            return true;
        }
        Node *temp = root;
        Node *prev = nullptr;
        while (temp != nullptr) {
            prev = temp;
            if (key == temp->key) {
                return false;
            }
            if (key < temp->key) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }
        if (key < prev->key) {
            prev->left = new Node(Node(key, value));
        } else {
            prev->right = new Node(Node(key, value));
        }
        _size++;
        return true;
    }

    int &size() {
        return this->_size;
    }

    void clear() {

    }

    bool isEmpty() {
        if (size())
            return true;
        else
            return false;
    }

    bool deleteByKey(K keyOfDeletable) { //fix
        Node *temp = root;
        Node *prev = nullptr;
        while (temp != nullptr && temp->key != keyOfDeletable) {
            prev = temp;
            keyOfDeletable < temp->key ? temp = temp->left : temp = temp->right;
        }
        if (temp == nullptr)
            return false;

        Node *x = nullptr;
        Node *y = nullptr;
        if (temp->left == nullptr && temp->right == nullptr) {
        } else if (temp->left == nullptr) {
            x = temp->right;
        } else if (temp->right == nullptr) {
            x = temp->left;
        } else {
            prev = temp;
            y = temp->right;
            while(y->left != nullptr) {
                prev = y;
                y = y->left;
            }
            temp->key = y->key;
            temp->value = y->value;
            x = y->right;
            temp = y;
        }
        if (prev == nullptr) {
            root = x;
        } else {
            if (temp->key < prev->key) {
                prev->left = x;
            } else {
                temp->right = x;
            }
        }
        delete temp;
        _size--;
        return true;
    }

    void show() {
        std::stack<Node *> stack;
        stack.push(root);
        while (!stack.empty()) {
            Node *temp = stack.top();
            stack.pop();
            std::cout << temp->key << " " << temp->value << std::endl;
            if (temp->right != nullptr)
                stack.push(temp->right);
            if (temp->left != nullptr)
                stack.push(temp->left);
        }
    }

    int numberOfKeysBiggerThen(K key) {

    }

    class Iterator;

    class ReverseIterator;

    Iterator begin() {

    }

    Iterator end() {

    }

    ReverseIterator rbegin() {

    }

    ReverseIterator rend() {

    }

};


#endif //ALGLAB2_BINARYSEARCHTREE_H
