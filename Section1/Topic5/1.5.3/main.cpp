// Раздел 1, тема 5, номер 3 - ПРОИЗВОЛЬНОЕ ДВОИЧНОЕ ДЕРЕВО

#include <iostream>

struct TreeNode {
    int data; // значение вершины
    TreeNode *left; // указатель на левую вершину
    TreeNode *right; // указатель на правую вершину
};

TreeNode *root;
TreeNode *detectedNode;
bool shouldContinue = true;

// Ввод целочисленного значения с проверкой
int failure() {
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
        break;
    }
    return choice;
}

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

// Функция проверки дерева на пустоту
bool isEmpty() {
    return root == nullptr;
}

// Функция добавления корня
void addRoot() {
    root = new TreeNode();
    std::cout << "\nДерево пустое. Введите значение для корневой вершины: ";
    root->data = failure();
    root->left = nullptr;
    root->right = nullptr;
    std::cout << "\nДобавлена корневая вершина со значением " << root->data << std::endl;
}

// Функция вывода дерева в обратно-симметричном порядке
void postOrderTraversal(TreeNode *pRoot, int level) {
    if (pRoot != nullptr) {
        postOrderTraversal(pRoot->right, level + 1); // рекурсивно вызываем функцию для правой ветки

        // Вывод отступов пропорциональных уровню вершины
        for (int i = 0; i < level * 5; i++) { // цикл для вывода отступов перед значением вершины
            std::cout << " ";
        }

        std::cout << pRoot->data << std::endl; // выводим значение корневой вершины
        postOrderTraversal(pRoot->left, level + 1); // рекурсивно вызываем функцию для левой ветки
    }
}

// Основное меню
void callMenu() {
    bool work{true};
    int choice;
    while (work) {
        std::cout << "_______________________________________________________________________";
        std::cout << "\nВведите номер команды: \n";
        std::cout << "1. Вывести текущее состояние дерева\n";
        std::cout << "2. Добавление вершины\n";
        std::cout << "3. Завершение работы\n";
        std::cout << "_______________________________________________________________________\n";
        std::cout << "Введите номер команды: ";
        choice = failure(1, 5);
        switch (choice) {
            case 1:
                if (isEmpty()) {
                    std::cout << "\nДерево пустое!\n";
                    break;
                }
                std::cout << "\nВывод дерева в обратно-симметричном порядке:\n";
                postOrderTraversal(root, 0);
                break;
            case 2:
                detectedNode = nullptr;
                shouldContinue = true;
                if (isEmpty()) {
                    addRoot();
                    break;
                }
                break;
            case 5:
                work = false;
                std::cout << "\nРабота программы завершена.\n";
                break;
            default:
                break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    callMenu();
}