// Раздел 1, тема 5, номер 2 - ИДЕАЛЬНО СБАЛАНСИРОВАННОЕ ДВОИЧНОЕ ДЕРЕВО (РЕКУРСИЯ + СТЕК)

#include <iostream>
#include <random>

struct TreeNode {
    int data; // значение вершины
    TreeNode *left; // указатель на левую вершину
    TreeNode *right; // указатель на правую вершину
};

struct StackItem {
    int level;
    TreeNode *prevNode; // указатель на пройденную вершину дерева
    StackItem *pNext;
};

int numberOfNodes; // количество вершин в дереве

// Ввод целочисленного значения с проверкой интервала
int failure(int begin, int end) {
    int choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "\nВведите данные правильно: ";
            continue;
        }
        std::cin.ignore(32767, '\n');
        if (choice < begin || choice > end) {
            std::cout << "\nВведите данные правильно: ";
            continue;
        }
        break;
    }
    return choice;
}

// Функция создания новой вершины
void newNode(TreeNode *&root, int n) {
    if (n == 0) { // если количество вершин равно нулю
        root = nullptr; // создается пустое дерево
    } else {
        int left_n = n / 2; // количество вершин в левом поддереве
        int right_n = n - left_n - 1; // количество вершин в правом поддереве
        root = new TreeNode; // выделение памяти под новую вершину
        std::random_device rd; // создание генератора случайных чисел
        std::mt19937 gen(rd()); // инициализация генератора
        std::uniform_int_distribution<> dis(0, 99); // задание диапазона случайных чисел
        root->data = dis(gen); // заполнение новой вершины случайным числом
        newNode(root->left, left_n); // рекурсивный вызов функции для создания левой вершины
        newNode(root->right, right_n); // рекурсивный вызов функции для создания правой вершины
    }
}

// Функция вывода дерева в прямом порядке
void preOrderTraversal(TreeNode *root, int level) { // root - указатель на корень дерева, level - уровень вершины
    if (root == nullptr) {
        return;
    }
    // Выводим значение вершины на экран, добавляя отступ в зависимости от ее уровня
    std::cout << std::string(level * 5, ' ') << root->data << std::endl;
    preOrderTraversal(root->left, level + 1); // рекурсивно вызываем функцию для левого поддерева
    preOrderTraversal(root->right, level + 1); // рекурсивно вызываем функцию для правого поддерева
}

// Функция вывода дерева в симметричном порядке (рекурсия)
void inOrderTraversal(TreeNode *root, int level) {
    if (root != nullptr) {
        inOrderTraversal(root->left, level + 1); // рекурсивный вызов для левого поддерева

        // Вывод отступов пропорциональных уровню вершины
        for (int i = 0; i < level * 5; i++) { // цикл для вывода отступов перед значением вершины
            std::cout << " ";
        }

        std::cout << root->data << std::endl; // вывод значения текущей вершины
        inOrderTraversal(root->right, level + 1); // рекурсивный вызов для правого поддерева
    }
}

// Функция вывода дерева в обратно-симметричном порядке
void postOrderTraversal(TreeNode *root, int level) {
    if (root != nullptr) {
        postOrderTraversal(root->right, level + 1); // рекурсивно вызываем функцию для правой ветки

        // Вывод отступов пропорциональных уровню вершины
        for (int i = 0; i < level * 5; i++) { // цикл для вывода отступов перед значением вершины
            std::cout << " ";
        }

        std::cout << root->data << std::endl; // выводим значение корневой вершины
        postOrderTraversal(root->left, level + 1); // рекурсивно вызываем функцию для левой ветки
    }
}

// Функция вывода дерева в симметричном порядке (стек)
// Принимает указатель на корневой узел дерева и указатель на вершину стека
void stackInOrderTraversal(TreeNode *root, StackItem *sp) {
    TreeNode *current = root; // инициализируем текущий узел как корневой узел
    bool stop = true; // флаг для остановки цикла
    int level = -1; // уровень текущего узла

    // Цикл будет выполняться, пока не пройдет все узлы дерева
    while (stop) {
        while (current != nullptr) { // пока текущий узел не является пустым
            auto *newItem = new StackItem; // создаем новый элемент стека
            level++; // увеличиваем уровень текущего узла
            newItem->level = level; // устанавливаем уровень элемента стека
            newItem->prevNode = current; // связываем элемент стека с текущим узлом
            newItem->pNext = sp; // связываем элемент стека с предыдущей вершиной стека
            sp = newItem; // обновляем указатель на вершину стека
            current = current->left; // переходим к левому узлу
        }
        if (sp == nullptr) { // если стек пуст
            stop = false; // устанавливаем флаг остановки цикла в false
        } else {
            current = sp->prevNode; // устанавливаем текущий узел как узел, предшествующий вершине стека
            level = sp->level; // устанавливаем уровень текущего узла как уровень вершины стека
            for (int i = 0; i < level * 5; i++) { // выводим отступы перед значением узла
                std::cout << " ";
            }
            std::cout << current->data << std::endl; // выводим значение текущего узла
            current = current->right; // переходим к правому узлу
            StackItem *temp = sp; // сохраняем указатель на вершину стека
            sp = sp->pNext; // обновляем указатель на вершину стека
            delete temp; // удаляем сохраненный указатель на вершину стека
        }
    }
}

// Основное меню
void callMenu(TreeNode *&treeRoot, StackItem *&sp) {
    bool work{true};
    while (work) {
        std::cout << "_______________________________________________________________________";
        std::cout << "\nВарианты команд:\n";
        std::cout << "1. Построение идеально сбалансированного двоичного дерева\n";
        std::cout << "2. Вывод дерева в прямом порядке\n";
        std::cout << "3. Вывод дерева в симметричном порядке (рекурсия)\n";
        std::cout << "4. Вывод дерева в симметричном порядке (стек)\n";
        std::cout << "5. Вывод дерева в обратно-симметричном порядке\n";
        std::cout << "6. Завершение работы\n";
        std::cout << "_______________________________________________________________________\n";
        std::cout << "Введите номер команды: ";
        int choice = failure(1, 6);
        switch (choice) {
            case 1:
                std::cout << "\nВведите количество вершин дерева (с учётом корня от 1 до 100): ";
                numberOfNodes = failure(1, 100);
                newNode(treeRoot, numberOfNodes);
                std::cout << std::endl;
                break;
            case 2:
                std::cout << "\nВывод дерева в прямом порядке:\n";
                preOrderTraversal(treeRoot, 0);
                break;
            case 3:
                std::cout << "\nВывод дерева в симметричном порядке (рекурсия):\n";
                inOrderTraversal(treeRoot, 0);
                break;
            case 4:
                std::cout << "\nВывод дерева в симметричном порядке (стек):\n";
                stackInOrderTraversal(treeRoot, sp);
                break;
            case 5:
                std::cout << "\nВывод дерева в обратно-симметричном порядке:\n";
                postOrderTraversal(treeRoot, 0);
                break;
            case 6:
                work = false;
                std::cout << "\nПрограмма завершена\n";
                break;
            default:
                break;
        }
    }
}


int main() {
    setlocale(LC_ALL, "RUS");
    auto *treeRoot = new TreeNode;
    StackItem *sp = nullptr;
    callMenu(treeRoot, sp);
}
