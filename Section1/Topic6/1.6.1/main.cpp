// Раздел 1, тема 6, номер 1 - ДВОИЧНОЕ ДЕРЕВО ПОИСКА

#include <iostream>
#include <random>

struct TreeNode {
    int key;
    int count;
    TreeNode *left;
    TreeNode *right;
};

TreeNode *root;
TreeNode *pTemp;
TreeNode *pCur;

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

// Функция вывода дерева в обратно-симметричном порядке
void printPostOrder(TreeNode *node, const std::string &prefix = "", bool isRight = false) {
    if (node != nullptr) {
        printPostOrder(node->right, prefix + (isRight ? "    " : "│   "), true);
        std::cout << prefix << (isRight ? "┌── " : "└── ") << node->key << std::endl;
        printPostOrder(node->left, prefix + (isRight ? "│   " : "    "), false);
    }
}

// Функция всех вершин в одну строку по порядку следования ключей
void printAllNodes(TreeNode *cur) {
    if (cur != nullptr) {
        printAllNodes(cur->left);
        std::cout << cur->key << " (" << cur->count << ")  ";
        printAllNodes(cur->right);
    }
}

// Функция поиска вершины по ключу
TreeNode *search(int searchKey) {
    pCur = root;
    while (pCur != nullptr) {
        if (pCur->key == searchKey) {
            return pCur;
        } else if (pCur->key > searchKey) {
            pCur = pCur->left;
        } else {
            pCur = pCur->right;
        }
    }
    return nullptr;
}

// Рекурсивная функция добавления новой вершины
void insertRecursive(TreeNode *&cur, int newKey) {
    if (cur == nullptr) {
        // Если достигнут конец дерева, создаем новую вершину и заполняем ее поля
        cur = new TreeNode;
        cur->key = newKey;
        cur->count = 1;
        cur->left = nullptr;
        cur->right = nullptr;
    } else if (newKey == cur->key) {
        // Если ключ уже существует, увеличиваем счетчик
        cur->count++;
    } else if (newKey < cur->key) {
        // Если новый ключ меньше текущего, рекурсивно добавляем в левое поддерево
        insertRecursive(cur->left, newKey);
    } else {
        // Иначе рекурсивно добавляем в правое поддерево
        insertRecursive(cur->right, newKey);
    }
}

// Нерекурсивная функция добавления новой вершины
void insertNonRecursive(int newKey) {
    if (root == nullptr) {
        root = new TreeNode();
        root->left = nullptr;
        root->right = nullptr;
        root->key = newKey;
        root->count = 1;
        return;
    }

    TreeNode *cur = root;
    TreeNode *prev = nullptr;

    while (cur != nullptr) {
        prev = cur;
        if (newKey < cur->key) cur = cur->left;
        else if (newKey > cur->key) cur = cur->right;
        else {
            cur->count++;
            return;
        }
    }

    auto *newNode = new TreeNode();
    newNode->key = newKey;
    newNode->count = 1;
    newNode->left = nullptr;
    newNode->right = nullptr;

    if (newKey < prev->key) {
        prev->left = newNode;
    } else {
        prev->right = newNode;
    }
}

// Функция удаления вершины (ближайшая большая вершина)
void remove(TreeNode *&pRoot, int key) {
    // Проверяем, была ли удалена вершина
    if (pRoot == nullptr) {
        std::cout << "Вершина с ключом " << key << " не найдена в дереве.\n";
    } else {
        if (key < pRoot->key) {
            remove(pRoot->left, key);
        } else if (key > pRoot->key) {
            remove(pRoot->right, key);
        } else {
            if (pRoot->left == nullptr) {
                TreeNode *temp = pRoot->right;
                delete pRoot;
                pRoot = temp;
                std::cout << "\nВершина с ключом " << key << " удалена из дерева.\n";
            } else if (pRoot->right == nullptr) {
                TreeNode *temp = pRoot->left;
                delete pRoot;
                pRoot = temp;
                std::cout << "\nВершина с ключом " << key << " удалена из дерева.\n";
            } else {
                TreeNode *min = pRoot->right;
                while (min->left != nullptr) {
                    min = min->left;
                }
                int minKey = min->key; // сохраняем значение ключа вершины-заменителя
                pRoot->key = minKey;
                remove(pRoot->right, minKey); // используем сохраненное значение
                std::cout << "\nВершина с ключом " << key << " удалена из дерева.\n";
                std::cout << "Новая вершина-заменитель: " << minKey << std::endl; // выводим сохраненное значение
            }
        }
    }
}

// Основное меню
void callMenu() {
    bool work = true;
    int choice;
    while (work) {
        std::cout << "___________________________________________________________________________________";
        std::cout << "\nВарианты команд:\n";
        std::cout << "1. Построение дерева поиска с заданным числом вершин\n";
        std::cout << "2. Вывод дерева в обратно-симметричном порядке\n";
        std::cout << "3. Вывод всех вершин в одну строку по порядку следования ключей (со счётчиками)\n";
        std::cout << "4. Добавление новой вершины с помощью рекурсивной функции\n";
        std::cout << "5. Добавление новой вершины с помощью нерекурсивной функции\n";
        std::cout << "6. Поиск вершины с заданным значением ключа\n";
        std::cout << "7. Удаление вершины с заданным значением ключа\n";
        std::cout << "8. Завершение работы\n";
        std::cout << "___________________________________________________________________________________\n";
        std::cout << "Введите номер команды: ";
        choice = failure(1, 8);
        int inputKey;
        switch (choice) {
            case 1:
                if (!isEmpty()) {
                    std::cout << "\nВаше дерево уже создано!\n";
                    break;
                }
                std::cout << "\nВведите число новых вершин (до 100): ";
                inputKey = failure(1, 100);
                for (int i = 0; i < inputKey; i++) {
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<int> distr(1, 100);
                    int key = distr(gen);
                    insertRecursive(root, key);
                }
                std::cout << "\nДерево успешно создано!\n";
                break;
            case 2:
                if (isEmpty()) {
                    std::cout << "\nДерево пустое!\n";
                    break;
                }
                std::cout << "\nВывод дерева в обратно-симметричном порядке:\n";
                printPostOrder(root);
                break;
            case 3:
                if (isEmpty()) {
                    std::cout << "\nДерево пустое!\n";
                    break;
                }
                std::cout << "\nВывод дерева в виде упорядоченной строки вершин: ";
                printAllNodes(root);
                std::cout << "\n";
                break;
            case 4:
                std::cout << "\nВведите значение добавляемого ключа: ";
                inputKey = failure();
                insertRecursive(root, inputKey);
                std::cout << "\nВершина с ключом " << inputKey << " рекурсивно добавлена в дерево." << std::endl;
                break;
            case 5:
                std::cout << "\nВведите значение добавляемого ключа: ";
                inputKey = failure();
                insertNonRecursive(inputKey);
                std::cout << "\nВершина с ключом " << inputKey << " нерекурсивно добавлена в дерево." << std::endl;
                break;
            case 6:
                if (isEmpty()) {
                    std::cout << "\nДерево пустое. Поиск невозможен!" << std::endl;
                    break;
                }
                std::cout << "\nВведите значение ключа, которого хотите найти: ";
                pTemp = search(failure());
                if (pTemp == nullptr) {
                    std::cout << "\nЗаданный элемент не найден!\n";
                } else {
                    std::cout << "\nЗаданный элемент найден. Счётчик: " << pTemp->count << std::endl;
                }
                break;
            case 7:
                if (isEmpty()) {
                    std::cout << "\nДерево пустое. Удаление невозможно!" << std::endl;
                    break;
                }
                std::cout << "\nВведите ключ удаляемой вершины: ";
                inputKey = failure();
                remove(root, inputKey);
                break;
            case 8:
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
    callMenu();
}
