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

    void showHelper(Node *t) {
        if (t == nullptr)
            return;
        showHelper(t->left);
        std::cout << t->key << " " << t->value << std::endl;
        showHelper(t->right);
    }

    T &searchHelper(Node *t, K key) {
        if (t == nullptr)
            throw std::exception();
        if (t->key == key)
            return t->value;
        if (key < t->key) {
            return searchHelper(t->left, key);
        } else {
            return searchHelper(t->right, key);
        }
    }

    bool addHelper(Node *current, K key, T value) {
        if (current->key == key)
            return false;
        if (current->key > key) {
            if (current->left == nullptr) {
                current->left = new Node(Node(key, value));
                _size++;
                return true;
            } else {
                return addHelper(current->left, key, value);
            }
        } else {
            if (current->right == nullptr) {
                current->right = new Node(Node(key, value));
                _size++;
                return true;
            } else {
                return addHelper(current->right, key, value);
            }
        }
    }

    Node *findMin(Node *current) {
        if (current->left == nullptr)
            return current;
        return findMin(current->left);
    }

    bool deleteHelper(Node *current, K key, Node *prev = nullptr) {
        if (current == nullptr)
            return false;
        if (current->key > key) {
            return deleteHelper(current->left, key, current);
        } else if (current->key < key) {
            return deleteHelper(current->right, key, current);
        } else {
            if (current->left == nullptr || current->right == nullptr) {
                Node *newNode = nullptr;
                if (current->left == nullptr) {
                    newNode = current->right;
                } else {
                    newNode = current->left;
                }
                if (prev != nullptr) {
                    if (prev->left == current) {
                        prev->left = newNode;
                    } else {
                        prev->right = newNode;
                    }
                } else {
                    root = newNode;
                }
                _size--;
                delete current;
                return true;
            } else {
                Node *temp = findMin(current->right);
                if (current->left != temp)
                    temp->left = current->left;
                if (current->right != temp)
                    temp->right = current->right;
                if (prev != nullptr) {
                    if (prev->left == current) {
                        prev->left = temp;
                    } else {
                        prev->right = temp;
                    }
                } else {
                    root = temp;
                }
                delete current;
                _size--;
                return true;
            }
        }
    }

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

    BinarySearchTree(const BinarySearchTree &otherTree) { //TODO

    }

    ~BinarySearchTree() { //TODO
    }

    T &recursiveSearch(K key) {
        return searchHelper(root, key);
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
        if (temp == nullptr)
            throw std::exception();
        return temp->value;

    }

    bool recursiveAdd(K key, T value) {
        if (root == nullptr) {
            root = new Node(Node(key, value));
            _size++;
            return true;
        } else {
            return addHelper(root, key, value);
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
        while(_size != 0) {
            recursiveDeleteByKey(root->key);
        }
    }

    bool isEmpty() {
        if (size())
            return true;
        else
            return false;
    }

    bool recursiveDeleteByKey(K keyOfDeletable) {
        if (root == nullptr)
            return false;
        return deleteHelper(root, keyOfDeletable);
    }

    void recursiveShow() {
        showHelper(root);
        std::cout << std::endl;
    }

    bool deleteByKey(K keyOfDeletable) {
        Node *current = root;
        Node *previous = nullptr;
        while (current != nullptr && current->key != keyOfDeletable) {
            previous = current;
            keyOfDeletable < current->key ?
                    current = current->left
                                          :
                    current = current->right;
        }
        if (current == nullptr)
            return false;

        if (current->left == nullptr || current->right == nullptr) {
            Node *newNode = nullptr;
            if (current->left == nullptr) {
                newNode = current->right;
            } else {
                newNode = current->left;
            }
            if (previous == nullptr) {
                delete root;
                root = newNode;
                _size--;
                return true;
            }
            if (current == previous->left)
                previous->left = newNode;
            else
                previous->right = newNode;
            delete current;
            _size--;
            return true;
        } else {
            previous = nullptr;
            Node *temp = current->right;

            while (temp->left != nullptr) {
                previous = temp;
                temp = temp->left;
            }

            if (previous != nullptr) {
                previous->left = temp->right;
            } else {
                current->right = temp->right;
            }
            current->value = temp->value;
            delete temp;
            _size--;
            return true;
        }
    }

    void show() {
        if (root != nullptr) {
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
