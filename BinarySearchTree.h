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

    Node *_parent_right(Node *t, Node *x) {
        if (t == x)
            return nullptr;
        if (x->key > t->key) {
            Node *rp = _parent_right(t->right, x);
            if (rp != nullptr)
                return rp;
            else
                return t;
        } else
            return _parent_right(t->left, x);
    }

    Node *_getPrev(Node *x) {
        if (x == nullptr)
            return nullptr;
        if (x->left != nullptr) {
            Node *temp = x->left;
            while (temp->right != nullptr)
                temp = temp->right;
            return temp;
        } else {
            return _parent_right(root, x);
        }
    }

    Node *_parent_left(Node *t, Node *x) {
        if (t == x)
            return nullptr;
        if (x->key < t->key) {
            Node *rp = _parent_left(t->left, x);
            if (rp != nullptr)
                return rp;
            else
                return t;
        } else
            return _parent_left(t->right, x);
    }

    Node *_getNext(Node *x) {
        if (x == nullptr)
            return nullptr;
        if (x->right != nullptr) {
            Node *temp = x->right;
            while (temp->left != nullptr)
                temp = temp->left;
            return temp;
        } else
            return _parent_left(root, x);
    }

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
                current->weight -= 1;
                _size++;
                return;
            } else {
                current->weight -= 1;
                return addBackN(current->left, key);
            }
        } else {
            if (current->right == nullptr) {
                current->weight -= 1;
                _size++;
                return;
            } else {
                current->weight -= 1;
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
                current->weight += 1;
                current->left = new Node(Node(key, value));
                _size++;
                return true;
            } else {
                current->weight += 1;
                return addHelper(current->left, key, value);
            }
        } else {
            if (current->right == nullptr) {
                current->weight += 1;
                current->right = new Node(Node(key, value));
                _size++;
                return true;
            } else {
                current->weight += 1;
                return addHelper(current->right, key, value);
            }
        }
    }

    Node *findMinDelete(Node *current, Node *prev, Node *deletable) {
        current->weight -= 1;
        if (current->left == nullptr) {
            if (current->right != nullptr && prev != deletable)
                prev->left = current->right;
            else if (prev != deletable)
                prev->left = nullptr;
            return current;
        }
        return findMinDelete(current->left, current, deletable);
    }

    Node* findMin(Node *current) {
        if (current->left == nullptr)
            return current;
        return findMin(current->left);
    }

    Node *findMax(Node *current) {
        if (current->right == nullptr)
            return current;
        return findMax(current->right);
    }

    void deleteBackN(Node *current, K key, Node *prev = nullptr) {
        if (current == nullptr) {
            return;
        }
        if (current->key > key) {
            current->weight += 1;
            return deleteBackN(current->left, key, current);
        } else if (current->key < key) {
            current->weight += 1;
            return deleteBackN(current->right, key, current);
        }
    }

    bool deleteHelper(Node *current, K key, Node *prev = nullptr) {
        if (current == nullptr) {
            deleteBackN(root, key);
            return false;
        }
        if (current->key > key) {
            current->weight -= 1;
            return deleteHelper(current->left, key, current);
        } else if (current->key < key) {
            current->weight -= 1;
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
                    if (newNode != nullptr)
                        newNode->weight = (root->weight) - 1;
                    root = newNode;
                }
                _size--;
                delete current;
                return true;
            } else {
                Node *temp = findMinDelete(current->right, current, current);
                if (current->left != temp) {
                    temp->left = current->left;
                    if (current->right != temp)
                        temp->right = current->right;
                } else {
                    temp->right = current->right;
                    if (current->left != temp)
                        temp->left = current->left;
                }
                if (prev != nullptr) {
                    temp->weight = current->weight - 1;
                    if (prev->left == current) {
                        prev->left = temp;
                    } else {
                        prev->right = temp;
                    }
                } else {
                    temp->weight = (root->weight) - 1;
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
        std::cout << current->key << " " << current->weight;
        std::cout << "\n";
        verticalShowHelper(current->left, level + 1);
    }

    void copyTree(Node *current) {
        if (current == nullptr)
            return;
        add(current->key, current->value);
        copyTree(current->left);
        copyTree(current->right);
    }

public:
    struct Node {
        Node *left;
        Node *right;
        K key;
        T value;
        int weight;

        Node(K key, T value, int _weight = 1) {
            this->left = nullptr;
            this->right = nullptr;
            this->key = key;
            this->value = value;
            weight = _weight;
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

    BinarySearchTree(const BinarySearchTree &otherTree) {
        _size = 0;
        root = nullptr;
        copyTree(otherTree.root);
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
            return false;
        else
            return true;
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

    int findIndex(K key) {
        if (root == nullptr)
            return -1;
        Node *searchNode = root;
        int indexNode = 0;
        if (searchNode->left != nullptr)
            indexNode = searchNode->left->weight;
        while (key != searchNode->key) {
            if (key > searchNode->key) {
                searchNode = searchNode->right;
                if (searchNode == nullptr)
                    return -1;
                if (searchNode->left != nullptr)
                    indexNode += searchNode->left->weight;
                indexNode += 1;

            } else {
                searchNode = searchNode->left;
                if (searchNode == nullptr)
                    return -1;
                if (searchNode->right != nullptr)
                    indexNode -= searchNode->right->weight;
                indexNode -= 1;
            }
        }
        return indexNode;
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
                    str += std::to_string(temp->weight);
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
        return Iterator(this);
    }

    Iterator end() {
        return Iterator(this, false);
    }

    ReverseIterator rbegin() {
        return ReverseIterator(this);
    }

    ReverseIterator rend() {
        return ReverseIterator(this, false);
    }


    class Iterator {
    private:
        BinarySearchTree<K, T> *tree;
        Node *current;
    public:
        Iterator(BinarySearchTree *_tree, bool isBegin = true) {
            if (_tree->isEmpty()) {
                tree = nullptr;
                current = nullptr;
            } else {
                tree = _tree;
                if (isBegin)
                    current = tree->findMin(tree->root);
                else
                    current = nullptr;
            }
        }

        Iterator(const Iterator &iterator) {
            tree = iterator.tree;
            current = iterator.current;
        }

        bool operator==(const Iterator &other) {
            if (other.tree != this->tree)
                return false;
            if (other.current != this->current)
                return false;
            return true;
        }

        bool operator!=(const Iterator &other) {
            if (other.tree != this->tree)
                return true;
            if (other.current != this->current)
                return true;
            return false;
        }

        Iterator &operator--(int) {
            current = tree->_getPrev(current);
            return *this;
        }

        Iterator &operator++(int) {
            current = tree->_getNext(current);
            return *this;
        }

        T &operator*() {
            if (current != nullptr)
                return current->value;
            else
                throw std::exception();
        }
    };

    class ReverseIterator {
    private:
        BinarySearchTree<K, T> *tree;
        Node *current;
    public:
        ReverseIterator(BinarySearchTree *_tree, bool isBegin = true) {
            if (_tree->isEmpty()) {
                tree = nullptr;
                current = nullptr;
            } else {
                tree = _tree;
                if (isBegin)
                    current = tree->findMax(tree->root);
                else
                    current = nullptr;
            }
        }

        ReverseIterator(const ReverseIterator &iterator) {
            tree = iterator.tree;
            current = iterator.current;
        }

        bool operator==(const ReverseIterator &other) {
            if (other.tree != this->tree)
                return false;
            if (other.current != this->current)
                return false;
            return true;
        }

        bool operator!=(const ReverseIterator &other) {
            if (other.tree != this->tree)
                return true;
            if (other.current != this->current)
                return true;
            return false;
        }

        ReverseIterator &operator--(int) {
            current = tree->_getNext(current);
            return *this;
        }

        ReverseIterator &operator++(int) {
            current = tree->_getPrev(current);
            return *this;
        }

        T &operator*() {
            if (current != nullptr)
                return current->value;
            else
                throw std::exception();
        }
    };

};


#endif //ALGLAB2_BINARYSEARCHTREE_H
