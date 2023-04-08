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

// Функция поиска вершины в дереве
void search(TreeNode *pNode, int intToFind) {
    if (shouldContinue && pNode != nullptr) {
        if (pNode->data == intToFind) {
            detectedNode = pNode;
            shouldContinue = false;
            std::cout << "\nВершина со значением " << intToFind << " найдена в дереве." << std::endl;
        }
        search(pNode->left, intToFind);
        search(pNode->right, intToFind);
    }
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

// Функция добавления левого потомка
void addLeft(TreeNode *pCurr) {
    std::cout << "У данной вершины нет левого потомка. Введите значение для добавления: ";
    int intToAdd = failure();
    auto *pTemp = new TreeNode();
    pTemp->left = nullptr;
    pTemp->right = nullptr;
    pTemp->data = intToAdd;
    pCurr->left = pTemp;
    std::cout << "\nДобавлена вершина со значением " << pTemp->data << " в качестве левого потомка.\n";
}

// Функция добавления правого потомка
void addRight(TreeNode *pCurr) {
    std::cout << "У данной вершины нет правого потомка. Введите значение для добавления: ";
    int intToAdd = failure();
    auto *pTemp = new TreeNode();
    pTemp->left = nullptr;
    pTemp->right = nullptr;
    pTemp->data = intToAdd;
    pCurr->right = pTemp;
    std::cout << "\nДобавлена вершина со значением " << pTemp->data << " в качестве правого потомка.\n";
}

// Функция добавления новой вершины
void addNewNode(TreeNode *pCurr, int whereToAdd) {
    std::cout << "\nВведите значение для новой вершины: ";
    int intToAdd = failure();
    auto *pTemp = new TreeNode();
    pTemp->left = nullptr;
    pTemp->right = nullptr;
    pTemp->data = intToAdd;
    if (whereToAdd == 1) {
        pCurr->left = pTemp;
        std::cout << "\nДобавлена вершина со значением " << pTemp->data << " в качестве левого потомка.\n";
    } else {
        pCurr->right = pTemp;
        std::cout << "\nДобавлена вершина со значением " << pTemp->data << " в качестве правого потомка.\n";
    }
}

// Функция добавления вершин
void addNodes(TreeNode *pCurr) {
    if (pCurr->left != nullptr && pCurr->right != nullptr) {
        std::cout << "У данной вершины уже есть оба потомка.\n";
    } else if (pCurr->left == nullptr && pCurr->right != nullptr) {
        addLeft(pCurr);
    } else if (pCurr->left != nullptr && pCurr->right == nullptr) {
        addRight(pCurr);
    } else {
        int whereToAdd;
        std::cout << "У данной вершины нет потомков. В какую сторону добавить новую вершину?";
        std::cout << "\n1. Влево\n2. Вправо\nВаш выбор: ";
        whereToAdd = failure(1, 2);
        addNewNode(pCurr, whereToAdd);
    }
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
        std::cout << "2. Добавление потомка вершины дерева\n";
        std::cout << "3. Поиск заданной вершины дерева\n";
        std::cout << "4. Завершение работы\n";
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
                std::cout << "\nВведите информационную часть вершины, которой следует добавить потомка: ";
                search(root, failure());
                if (detectedNode == nullptr) {
                    std::cout << "\nТакой вершины не существует!\n";
                } else {
                    addNodes(detectedNode);
                }
                break;
            case 3:
                detectedNode = nullptr;
                shouldContinue = true;
                if (isEmpty()) {
                    std::cout << "\nДерево пустое. Поиск невозможен!" << std::endl;
                    break;
                }
                std::cout << "\nВведите значение вершины, которую хотите найти: ";
                search(root, failure());
                if (detectedNode == nullptr) {
                    std::cout << "\nВершина не найдена в дереве." << std::endl;
                }
                break;
            case 4:
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