//
// Created by sasha on 19.10.2022.
//

#ifndef ALGLAB2_BINARYSEARCHTREE_H
#define ALGLAB2_BINARYSEARCHTREE_H

template<class K, class T>
class BinarySearchTree {
public:
    struct Node;
private:
    Node *root{};
    int _size;
    int count;

    Node *_parent_right(Node *t, Node *x) { //Поиск правого родителя
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

    Node *_getPrev(Node *x) { //Получение предыдущего элемента
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

    Node *_parent_left(Node *t, Node *x) { //Поиск левого родителя
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

    Node *_getNext(Node *x) { //Получение следующего элемента
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

    void showHelper(Node *t) { //Метод помощник для реализации обхода
        if (t == nullptr)
            return;
        std::cout << t->key << " " << t->value << std::endl;
        showHelper(t->left);
        showHelper(t->right);
    }

    T &searchHelper(Node *t, K key) { //Метод помощник для реализации поиска
        count++;
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

    void addBackN(Node *current, K key) { //Метод для отмены изменений веса при вставке
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

    bool addHelper(Node *current, K key, T value) { //Метод помощник для реализации вставки
        count++;
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

    Node *findMinDelete(Node *current, Node *prev, Node *deletable) { //Метод для поиска минимального узла при удалении
        count++;
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

    Node* findMin(Node *current) { //Метод для поиска минимального узла
        if (current->left == nullptr)
            return current;
        return findMin(current->left);
    }

    Node *findMax(Node *current) { //Метод для поиска максимального узла
        if (current->right == nullptr)
            return current;
        return findMax(current->right);
    }

    void deleteBackN(Node *current, K key, Node *prev = nullptr) { //Метод для отмены изменений веса при удалении
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

    bool deleteHelper(Node *current, K key, Node *prev = nullptr) { //Метод помощник для реализации удаления
        count++;
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

    void verticalShowHelper(Node *current, int level = 1) { //Метод помошник для вертикального показа дерева
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

    void copyTree(Node *current) { //Метод для копирования дерева
        if (current == nullptr)
            return;
        add(current->key, current->value);
        copyTree(current->left);
        copyTree(current->right);
    }

public:
    struct Node { //Структура узла дерева
        Node *left;
        Node *right;
        K key;
        T value;
        int weight;

        Node(K key, T value, int _weight = 1) { //Конструктор
            this->left = nullptr;
            this->right = nullptr;
            this->key = key;
            this->value = value;
            weight = _weight;
        }
    };

    BinarySearchTree() { //Конструктор
        root = nullptr;
        _size = 0;
        count = 0;
    }

    BinarySearchTree(K key, T value) { //Конструктор с параметрами
        root = new Node(Node(key, value));
        _size = 0;
        count = 0;
    }

    BinarySearchTree(const BinarySearchTree &otherTree) { //Конструктор копирования
        _size = 0;
        root = nullptr;
        copyTree(otherTree.root);
        count = 0;
    }

    ~BinarySearchTree() { //Деструктор
        this->clear();
    }

    T &search(K key) { //Доступ к данным по заданному ключу
        return searchHelper(root, key);
    }

    bool add(K key, T value) { //Включение данных с заданным ключом
        if (root == nullptr) {
            count++;
            root = new Node(Node(key, value));
            _size++;
            return true;
        } else {
            return addHelper(root, key, value);
        }
    }

    int &size() { //Опрос размера дерева
        return this->_size;
    }

    void clear() { //Очистка дерева
        while (_size != 0) {
            deleteByKey(root->key);
        }
    }

    bool isEmpty() { //Проверка дерева на пустоту
        if (size())
            return false;
        else
            return true;
    }

    bool deleteByKey(K keyOfDeletable) { //Удаление данных с заданным ключем
        if (root == nullptr)
            return false;
        return deleteHelper(root, keyOfDeletable);
    }

    void show() { //Обход узлов дерева
        showHelper(root);
        std::cout << std::endl;
    }

    int countNode() { //Операция для сброса счетчика
        int temp = count;
        count = 0;
        return temp;
    }

    int findIndex(K key) { //Операция для поиска индекса узла по ключу
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

    void verticalShow() { //Вертикальный показ дерева
        verticalShowHelper(root);
    }

    class Iterator; //Объявление прямого итератора

    class ReverseIterator; //Объявление обратного итератора

    Iterator begin() { //Запрос прямого итератора
        return Iterator(this);
    }

    Iterator end() { //Запрос “неустановленного” прямого итератора
        return Iterator(this, false);
    }

    ReverseIterator rbegin() { //Запрос обратного итератора
        return ReverseIterator(this);
    }

    ReverseIterator rend() { //Запрос “неустановленного” обратного итератора
        return ReverseIterator(this, false);
    }

//Итераторы
    class Iterator {//Прямой итератор
    private:
        BinarySearchTree<K, T> *tree; //Указатель на дерево
        Node *current; //Указатель на текущий элемент итератора
    public:
        Iterator(BinarySearchTree *_tree, bool isBegin = true) { //Конструктор
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

        Iterator(const Iterator &iterator) { //Конструктор копирования
            tree = iterator.tree;
            current = iterator.current;
        }

        bool operator==(const Iterator &other) { //Оператор ==
            if (other.tree != this->tree)
                return false;
            if (other.current != this->current)
                return false;
            return true;
        }

        bool operator!=(const Iterator &other) { //Оператор !=
            if (other.tree != this->tree)
                return true;
            if (other.current != this->current)
                return true;
            return false;
        }

        Iterator &operator--(int) { //Оператор --
            current = tree->_getPrev(current);
            return *this;
        }

        Iterator &operator++(int) { //Оператор ++
            current = tree->_getNext(current);
            return *this;
        }

        T &operator*() { //Оператор *
            if (current != nullptr)
                return current->value;
            else
                throw std::exception();
        }
    };

    class ReverseIterator { //Обратный итератор
    private:
        BinarySearchTree<K, T> *tree; //Указатель на дерево
        Node *current; //Указатель на текущий элемент итератора
    public:
        ReverseIterator(BinarySearchTree *_tree, bool isBegin = true) { //Конструктор
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

        ReverseIterator(const ReverseIterator &iterator) { //Конструктор копирования
            tree = iterator.tree;
            current = iterator.current;
        }

        bool operator==(const ReverseIterator &other) { //Оператор ==
            if (other.tree != this->tree)
                return false;
            if (other.current != this->current)
                return false;
            return true;
        }

        bool operator!=(const ReverseIterator &other) { //Оператор !=
            if (other.tree != this->tree)
                return true;
            if (other.current != this->current)
                return true;
            return false;
        }

        ReverseIterator &operator--(int) { //Оператор --
            current = tree->_getNext(current);
            return *this;
        }

        ReverseIterator &operator++(int) { //Оператор ++
            current = tree->_getPrev(current);
            return *this;
        }

        T &operator*() { //Оператор *
            if (current != nullptr)
                return current->value;
            else
                throw std::exception();
        }
    };

};


#endif //ALGLAB2_BINARYSEARCHTREE_H
