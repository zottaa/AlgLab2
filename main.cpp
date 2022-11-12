#include <iostream>
#include "BinarySearchTree.h"

template<class K, class T>
void menu(BinarySearchTree<K, T> &tree,
          typename BinarySearchTree<K, T>::Iterator &iterator,
          typename BinarySearchTree<K, T>::ReverseIterator &reverseIterator) {
    int value = 0;
    while (value != 22) {
        std::cout << "0 - show tree vertically\n"
                     "1 - show size\n"
                     "2 - clear tree\n"
                     "3 - isEmpty\n"
                     "4 - search\n"
                     "5 - search(set)\n"
                     "6 - add\n"
                     "7 - delete\n"
                     "8 - show list\n"
                     "9 - find index\n"
                     "10 - iterator begin\n"
                     "11 - iterator end\n"
                     "12 - iterator++\n"
                     "13 - iterator--\n"
                     "14 - iterator*\n"
                     "15 - iterator*(set)\n"
                     "16 - reverse iterator begin\n"
                     "17 - reverse iterator end\n"
                     "18 - reverse iterator++\n"
                     "19 - reverse iterator--\n"
                     "20 - reverse iterator*\n"
                     "21 - reverse iterator*(set)\n"
                     "22 - exit\n";


        std::cin >> value;
        switch (value) {
            case 0: {
                tree.verticalShow();
                break;
            }
            case 1: {
                std::cout << tree.size() << std::endl;
                break;
            }
            case 2: {
                tree.clear();
                break;
            }
            case 3: {
                std::cout << tree.isEmpty() << std::endl;
                break;
            }
            case 4: {
                std::cout << "enter key: ";
                K key;
                std::cin >> key;
                std::cout << tree.search(key) << std::endl;
                break;
            }
            case 5: {
                std::cout << "key and new value";
                K key;
                T item;
                std::cin >> key >> item;
                T temp = tree.search(key);
                temp = item;
                break;
            }
            case 6: {
                std::cout << "enter key and value: ";
                T item;
                K key;
                std::cin >> key >> item;
                std::cout << std::endl << tree.add(key, item) << std::endl;
                break;
            }
            case 7: {
                std::cout << "enter key ";
                K key;
                std::cin >> key;
                std::cout << std::endl << tree.deleteByKey(key) << std::endl;
                break;
            }
            case 8: {
                tree.show();
                break;
            }
            case 9: {
                std::cout << "enter key: ";
                K key;
                std::cin >> key;
                std::cout << tree.findIndex(key) << std::endl;
                break;
            }
            case 10: {
                iterator = tree.begin();
                break;
            }
            case 11: {
                iterator = tree.end();
                break;
            }
            case 12: {
                iterator++;
                break;
            }
            case 13: {
                iterator--;
                break;
            }
            case 14: {
                try {
                    std::cout << *iterator << std::endl;
                }
                catch (std::exception &) {
                    std::cout << "Exception!" << std::endl;
                }
                break;
            }
            case 15: {
                try {
                    std::cout << "enter value: ";
                    T item;
                    std::cin >> item;
                    T temp = *iterator;
                    temp = item;
                }
                catch (std::exception &) {
                    std::cout << "Exception!" << std::endl;
                }
                break;
            }
            case 16: {
                reverseIterator = tree.rbegin();
                break;
            }
            case 17: {
                reverseIterator = tree.rend();
                break;
            }
            case 18: {
                reverseIterator++;
                break;
            }
            case 19: {
                reverseIterator--;
                break;
            }
            case 20: {
                try {
                    std::cout << *reverseIterator << std::endl;
                } catch (std::exception &) {
                    std::cout << "Exception!";
                }
                break;
            }
            case 21: {
                try {
                    std::cout << "enter value: ";
                    T item;
                    std::cin >> item;
                    T temp = *reverseIterator;
                    temp = item;
                }
                catch (std::exception &) {
                    std::cout << "Exception!" << std::endl;
                }
                break;
            }
            default:
                break;
        }
    }
}


int main() {
    BinarySearchTree<int, int> tree;
    BinarySearchTree<int, int>::Iterator iterator(tree.begin());
    BinarySearchTree<int, int>::ReverseIterator reverseIterator(tree.rbegin());

    menu<int,int>(tree, iterator, reverseIterator);
}