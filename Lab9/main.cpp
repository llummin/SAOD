// Лабораторная работа №9 (раздел 1, тема 5, номер 1) - ИДЕАЛЬНО СБАЛАНСИРОВАННОЕ ДВОИЧНОЕ ДЕРЕВО (РЕКУРСИВНЫЙ ВАРИАНТ)

#include <iostream>
#include <random>

struct TreeNode {
    int data; // значение вершины
    TreeNode *left; // указатель на левую вершину
    TreeNode *right; // указатель на правую вершину
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

// Основное меню
void callMenu(TreeNode *&treeRoot) {
    bool work{true};
    while (work) {
        std::cout << "_______________________________________________________________________";
        std::cout << "\nВарианты команд:\n";
        std::cout << "1. Построение идеально сбалансированного двоичного дерева\n";
        std::cout << "2. Вывод дерева в прямом порядке\n";
        std::cout << "3. Завершение работы\n";
        std::cout << "_______________________________________________________________________\n";
        std::cout << "Введите номер команды: ";
        int choice = failure(1, 5);
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
    callMenu(treeRoot);
}