// Раздел 1, тема 5, номер 3 - ПРОИЗВОЛЬНОЕ ДВОИЧНОЕ ДЕРЕВО

#include <iostream>

struct TreeNode {
    int data; // значение вершины
    TreeNode *left; // указатель на левую вершину
    TreeNode *right; // указатель на правую вершину
};

// Объявление указателей на корень дерева и на узел, который будет найден
TreeNode *root;
TreeNode *detectedNode;

// Флаг, который используется для определения, продолжать ли поиск
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
    // Если дерево не пустое и поиск еще не закончен
    if (shouldContinue && pNode != nullptr) {
        if (pNode->data == intToFind) { // если нашли узел с нужным значением
            detectedNode = pNode; // сохраняем найденный узел
            shouldContinue = false; // устанавливаем флаг, чтобы прекратить поиск
            std::cout << "\nВершина со значением " << intToFind << " найдена в дереве." << std::endl;
        }
        search(pNode->left, intToFind); // рекурсивный вызов функции для левого поддерева
        search(pNode->right, intToFind); // рекурсивный вызов функции для правого поддерева
    }
}

// Функция добавления корня
void addRoot() {
    root = new TreeNode(); // выделяем память под новый узел
    std::cout << "\nДерево пустое. Введите значение для корневой вершины: ";
    root->data = failure(); // считываем значение для корня
    root->left = nullptr; // указатель на левое поддерево инициализируем как nullptr
    root->right = nullptr; // указатель на правое поддерево инициализируем как nullptr
    std::cout << "\nДобавлена корневая вершина со значением " << root->data << std::endl;
}

// Функция добавления левого потомка
void addLeft(TreeNode *pCurr) {
    std::cout << "У данной вершины нет левого потомка. Введите значение для добавления: ";
    int intToAdd = failure(); // вызов функции для получения значения
    auto *pTemp = new TreeNode(); // создание новой вершины и сохранение указателя на неё в pTemp
    pTemp->left = nullptr; // инициализация левого потомка новой вершины как nullptr
    pTemp->right = nullptr; // инициализация правого потомка новой вершины как nullptr
    pTemp->data = intToAdd; // инициализация значения новой вершины как intToAdd
    pCurr->left = pTemp; // установка новой вершины в качестве левого потомка текущей вершины
    std::cout << "\nДобавлена вершина со значением " << pTemp->data << " в качестве левого потомка.\n";
}

// Функция добавления правого потомка
void addRight(TreeNode *pCurr) {
    std::cout << "У данной вершины нет правого потомка. Введите значение для добавления: ";
    int intToAdd = failure();
    // Создание новой вершины и присвоение значение intToAdd
    auto *pTemp = new TreeNode();
    pTemp->left = nullptr;
    pTemp->right = nullptr;
    pTemp->data = intToAdd;
    // Присвоение указателю pCurr->right адреса созданной вершины pTemp
    pCurr->right = pTemp;
    // Вывод сообщения о том, что вершина успешно добавлена и какое значение она имеет
    std::cout << "\nДобавлена вершина со значением " << pTemp->data << " в качестве правого потомка.\n";
}

// Функция добавления новой вершины
void addNewNode(TreeNode *pCurr, int whereToAdd) {
    std::cout << "\nВведите значение для новой вершины: ";
    int intToAdd = failure();
    // Создание новой вершины и присвоение значение intToAdd
    auto *pTemp = new TreeNode();
    pTemp->left = nullptr;
    pTemp->right = nullptr;
    pTemp->data = intToAdd;
    // Проверка, куда добавлять новую вершину
    if (whereToAdd == 1) {
        // Присвоение указателю pCurr->left адреса созданной вершины pTemp и вывод сообщения об успешном добавлении
        pCurr->left = pTemp;
        std::cout << "\nДобавлена вершина со значением " << pTemp->data << " в качестве левого потомка.\n";
    } else {
        // Присвоение указателю pCurr->right адреса созданной вершины pTemp и вывод сообщения об успешном добавлении
        pCurr->right = pTemp;
        std::cout << "\nДобавлена вершина со значением " << pTemp->data << " в качестве правого потомка.\n";
    }
}

// Функция добавления вершин
void addNodes(TreeNode *pCurr) {
    if (pCurr->left != nullptr && pCurr->right != nullptr) { // если у текущей вершины уже есть оба потомка
        std::cout << "У данной вершины уже есть оба потомка.\n";
    } else if (pCurr->left == nullptr && pCurr->right != nullptr) { // если у текущей вершины есть только правый потомок
        addLeft(pCurr);
    } else if (pCurr->left != nullptr && pCurr->right == nullptr) { // если у текущей вершины есть только левый потомок
        addRight(pCurr);
    } else { // если у текущей вершины нет потомков, запрашиваем у пользователя
        int whereToAdd;
        std::cout << "У данной вершины нет потомков. В какую сторону добавить новую вершину?";
        std::cout << "\n1. Влево\n2. Вправо\nВаш выбор: ";
        whereToAdd = failure(1, 2);
        addNewNode(pCurr, whereToAdd);
    }
}

// Уничтожение всего дерева
void destroyTree(TreeNode *node) {
    // Если вершина не равна nullptr, вызываем функцию destroyTree для левого и правого потомков
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        std::cout << "Удалена вершина, со значением: " << node->data << std::endl;
        delete node;
    }
}

// Функция вывода дерева в обратно-симметричном порядке
void printTree(TreeNode *pRoot, int level) {
    if (pRoot != nullptr) {
        printTree(pRoot->right, level + 1); // рекурсивно вызываем функцию для правой ветки

        // Вывод отступов пропорциональных уровню вершины
        for (int i = 0; i < level * 5; i++) { // цикл для вывода отступов перед значением вершины
            std::cout << " ";
        }

        std::cout << pRoot->data << std::endl; // выводим значение корневой вершины
        printTree(pRoot->left, level + 1); // рекурсивно вызываем функцию для левой ветки
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
        std::cout << "3. Удаление дерева\n";
        std::cout << "4. Поиск заданной вершины дерева\n";
        std::cout << "5. Завершение работы\n";
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
                printTree(root, 0);
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
                if (isEmpty()) {
                    std::cout << "\nДерево пустое. Удаление невозможно! \n";
                    break;
                }
                destroyTree(root);
                root = nullptr;
                std::cout << "\nДерево успешно уничтожено!\n";
                break;
            case 4:
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