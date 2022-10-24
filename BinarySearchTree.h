//
// Created by sasha on 19.10.2022.
//

#ifndef ALGLAB2_BINARYSEARCHTREE_H
#define ALGLAB2_BINARYSEARCHTREE_H

#include <stack>
#include <string>

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

    void addBackN(Node *current, K key) {
        if (current->key == key)
            return;
        if (current->key > key) {
            if (current->left == nullptr) {
                current->n -= 1;
                _size++;
                return;
            } else {
                current->n -= 1;
                return addBackN(current->left, key);
            }
        } else {
            if (current->right == nullptr) {
                current->n -= 1;
                _size++;
                return;
            } else {
                current->n -= 1;
                return addBackN(current->right, key);
            }
        }
    }

    bool addHelper(Node *current, K key, T value) {
        if (current->key == key) {
            addBackN(root, key);
            return false;
        }
        if (current->key > key) {
            if (current->left == nullptr) {
                current->n += 1;
                current->left = new Node(Node(key, value));
                _size++;
                return true;
            } else {
                current->n += 1;
                return addHelper(current->left, key, value);
            }
        } else {
            if (current->right == nullptr) {
                current->n += 1;
                current->right = new Node(Node(key, value));
                _size++;
                return true;
            } else {
                current->n += 1;
                return addHelper(current->right, key, value);
            }
        }
    }

    Node *findMin(Node *current) {
        if (current->left == nullptr)
            return current;
        return findMin(current->left);
    }

    void deleteBackN(Node *current, K key, Node *prev = nullptr) {
        if (current == nullptr) {
            return;
        }
        if (current->key > key) {
            current->n += 1;
            return deleteBackN(current->left, key, current);
        } else if (current->key < key) {
            current->n += 1;
            return deleteBackN(current->right, key, current);
        }
    }

    bool deleteHelper(Node *current, K key, Node *prev = nullptr) { //TODO (n reduce)
        if (current == nullptr) {
            deleteBackN(root, key);
            return false;
        }
        if (current->key > key) {
            current->n -= 1;
            return deleteHelper(current->left, key, current);
        } else if (current->key < key) {
            current->n -= 1;
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
                    newNode->n = (root->n) - 1;
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
                    temp->n = (root->n) - 1;
                    root = temp;
                }
                delete current;
                _size--;
                return true;
            }
        }
    }

    void verticalShowHelper(Node *current, int level = 1) {
        if (current == nullptr)
            return;
        verticalShowHelper(current->right, level + 1);
        for (int i = 0; i != level * 3; ++i) {
            std::cout << " ";
        }
        std::cout << current->key << " " << current->n;
        std::cout << "\n";
        verticalShowHelper(current->left, level + 1);
    }

public:
    struct Node {
        Node *left;
        Node *right;
        K key;
        T value;
        int n;

        Node(K key, T value, int _n = 1) {
            this->left = nullptr;
            this->right = nullptr;
            this->key = key;
            this->value = value;
            n = _n;
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

    ~BinarySearchTree() {
        this->clear();
    }

    T &search(K key) {
        return searchHelper(root, key);
    }

    bool add(K key, T value) {
        if (root == nullptr) {
            root = new Node(Node(key, value));
            _size++;
            return true;
        } else {
            return addHelper(root, key, value);
        }
    }

    int &size() {
        return this->_size;
    }

    void clear() {
        while (_size != 0) {
            deleteByKey(root->key);
        }
    }

    bool isEmpty() {
        if (size())
            return true;
        else
            return false;
    }

    bool deleteByKey(K keyOfDeletable) {
        if (root == nullptr)
            return false;
        return deleteHelper(root, keyOfDeletable);
    }

    void show() {
        showHelper(root);
        std::cout << std::endl;
    }

    int findNumber(K key) { //TODO
        if (root == nullptr)
            throw std::exception();
    }

    void verticalShow() {
        verticalShowHelper(root);
    }

    std::string toString() {
        std::string str;
        Node *temp = root;
        if (temp != nullptr) {
            std::stack<Node *> stack;
            while (!stack.empty() || temp != nullptr) {
                if (temp != nullptr) {
                    stack.push(temp);
                    temp = temp->left;
                } else {
                    temp = stack.top();
                    str += std::to_string(temp->key);
                    stack.pop();
                    temp = temp->right;
                }
            }
        }
        return str;
    }

    std::string toStringN() {
        std::string str;
        Node *temp = root;
        if (temp != nullptr) {
            std::stack<Node *> stack;
            while (!stack.empty() || temp != nullptr) {
                if (temp != nullptr) {
                    stack.push(temp);
                    temp = temp->left;
                } else {
                    temp = stack.top();
                    str += std::to_string(temp->n);
                    stack.pop();
                    temp = temp->right;
                }
            }
        }
        return str;
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
