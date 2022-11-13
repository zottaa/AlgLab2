#include <iostream>
#include "BinarySearchTree.h"
#include <ctime>
#include <cmath>
using namespace std;
typedef unsigned long long INT_64;

//переменная и константы генератора LineRand()
static INT_64 RRand=15750;
const INT_64 mRand =(1<<63)-1;
const INT_64 aRand=6364136223846793005;
const INT_64 cRand=1442695040888963407;
//функция установки первого случайного числа от часов
//компьютера
void sRand () { srand(time(0)); RRand=(INT_64)rand();}
//функция генерации случайного числа
//линейный конгруэнтный генератор Xi+1=(a*Xi+c)%m
//habr.com/ru/post/208178
INT_64 LineRand ()
{
    INT_64 y1,y2;
    y1= (aRand*RRand+cRand)%mRand;
    y2= (aRand*y1+cRand)%mRand;
    RRand = y1 & 0xFFFFFFFF00000000LL ^ (y2 &
                                         0xFFFFFFFF00000000LL)>>32;
    return RRand;
}

void test_rand(int n)
{
    //создание дерева для 64 – разрядных ключей типа INT_64
    BinarySearchTree< INT_64,int > tree;
    //массив для ключей, которые присутствуют в дереве
    INT_64* m=new INT_64 [n];
//установка первого случайного числа
    sRand();
//заполнение дерева и массива элементами
//со случайными ключами
    for(int i=0; i<n; i++)
    {
        m[i]=LineRand();
        tree.add(m[i],1);
    }
//вывод размера дерева до теста
    cout<<"items count:"<<tree.size()<<endl;
//обнуление счётчиков трудоёмкости вставки,
//удаления и поиска
    tree.countNode();
    double I=0;
    double D=0;
    double S=0;
//генерация потока операций, 10% - промахи операций
    for(int i=0;i<n/2;i++)
        if(i%10==0) //10% промахов
        {
            tree.deleteByKey(LineRand ());
            D+=tree.countNode();
            tree.add(m[rand()%n],1);
            I+=tree.countNode();
            try{
                tree.search(LineRand ());
                S+=tree.countNode();
            }
                //обработка исключения при ошибке операции поиска
            catch(std::exception& ){S+=tree.countNode();}}
        else //90% успешных операций
        {
            int ind=rand()%n;
            tree.deleteByKey(m[ind]);
            D+=tree.countNode();
            INT_64 key=LineRand ();
            tree.add(key,1);
            I+=tree.countNode();
            m[ind]=key;
            try{
                tree.search(m[rand()%n]);
                S+=tree.countNode();
            }
            //обработка исключения при ошибке операции поиска
            catch(std::exception& ){S+=tree.countNode();}
        } //конец теста
//вывод результатов:
//вывод размера дерева после теста
    cout<<"items count:"<<tree.size()<<endl;
//теоретической оценки трудоёмкости операций BST
    cout<<"1.39*log2(n)="<<1.39*(log((double)n)/log(2.0))<<endl;
//экспериментальной оценки трудоёмкости вставки
    cout<<"Count insert: " << I/(n/2) <<endl;
//экспериментальной оценки трудоёмкости удаления
    cout<<"Count delete: " << D/(n/2) <<endl;
//экспериментальной оценки трудоёмкости поиска
    cout<<"Count search: " << S/(n/2) <<endl;
//освобождение памяти массива m[]
    delete[] m;
}

void test_ord(int n)
{
    //создание дерева для 64 – разрядных ключей типа INT_64
    BinarySearchTree< INT_64,int > tree;
    //массив для ключей, которые присутствуют в дереве
    INT_64* m=new INT_64 [n];
//заполнение дерева и массива элементами
// с возрастающими чётными ключами
//на интервале [0, 10000, 20000, ... ,10000*n]
    for(int i=0; i<n; i++) {
        m[i]= i*10000;
        tree.add(m[i],1);
    }
//вывод размера дерева до теста
    cout<<"items count:"<<tree.size()<<endl;
//обнуление счётчиков трудоёмкости вставки,
// удаления и поиска
    tree.countNode();
    double I=0;
    double D=0;
    double S=0;
//установка первого случайного числа
    sRand ();
//генерация потока операций, 10% - промахи операций
    for(int i=0;i<n/2;i++)
    {
        if(i%10==0) //10% промахов
        {int k=LineRand()%(10000*n);
            k=k+!(k%2); //случайный нечётный ключ
            tree.deleteByKey(k);
            D+=tree.countNode();
            tree.add(m[rand()%n],1);
            I+=tree.countNode();
            k=LineRand()%(10000*n);
            k=k+!(k%2); // случайный нечётный ключ
            try{
                tree.search(k);
                S+=tree.countNode();
            }
                //обработка исключения при ошибке операции поиска
            catch(std::exception&){S+=tree.countNode();}
        }
        else //90% успешных операций
        {
            int ind=rand()%n;
            tree.deleteByKey(m[ind]);
            D+=tree.countNode();;
            int k=LineRand()%(10000*n);
            k=k+k%2; // случайный чётный ключ
            tree.add(k,1);
            I+=tree.countNode();;
            m[ind]=k;
            try{
                tree.search(m[rand()%n]);
                S+=tree.countNode();;
            }
                //обработка исключения при ошибке операции поиска
            catch(std::exception&){S+=tree.countNode();}
        }
    }
//вывод результатов:
// вывод размера дерева после теста
    cout<<"items count:"<<tree.size()<<endl;
//теоретической оценки трудоёмкости операций BST
    cout<<"n/2 ="<<n/2<<endl;
//экспериментальной оценки трудоёмкости вставки
    cout<<"Count insert: " << I/(n/2) <<endl;
//экспериментальной оценки трудоёмкости удаления
    cout<<"Count delete: " << D/(n/2) <<endl;
//экспериментальной оценки трудоёмкости поиска
    cout<<"Count search: " << S/(n/2) <<endl;
//освобождение памяти массива m[]
    delete[] m;
} //конец теста

template<class K, class T>
void menu(BinarySearchTree<K, T> &tree,
          typename BinarySearchTree<K, T>::Iterator &iterator,
          typename BinarySearchTree<K, T>::ReverseIterator &reverseIterator) {
    int value = 0;
    while (value != 24) {
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
                     "22 - rand_test\n"
                     "23 - ord_test\n"
                     "24 - exit\n";


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
            case 22: {
                std::cout << "enter n: ";
                int n = 0;
                std::cin >> n;
                std::cout << std::endl;
                test_rand(n);
                break;
            }
            case 23: {
                std::cout << "enter n: ";
                int n = 0;
                std::cin >> n;
                std::cout << std::endl;
                test_ord(n);
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