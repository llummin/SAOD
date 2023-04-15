// Раздел 1, тема 6, номер 1 - ДВОИЧНОЕ ДЕРЕВО ПОИСКА

#include <iostream>
#include <random>

struct TreeNode {
    int key;  // ключ вершины
    int count;  // счетчик количества вершин с таким же ключом
    TreeNode *left;  // указатель на левое поддерево
    TreeNode *right;  // указатель на правое поддерево
};

TreeNode *root; // указатель на корень дерева
TreeNode *pTemp; // указатель на временную вершину
TreeNode *pCur; // указатель на текущую вершину

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
        // Рекурсивный вызов для правого поддерева
        printPostOrder(node->right, prefix + (isRight ? "    " : "│   "), true);
        // Вывод вершины
        std::cout << prefix << (isRight ? "┌── " : "└── ") << node->key << std::endl;
        // Рекурсивный вызов для левого поддерева
        printPostOrder(node->left, prefix + (isRight ? "│   " : "    "), false);
    }
}

// Функция вывода всех вершин в одну строку по порядку следования ключей
void printAllNodes(TreeNode *cur) {
    if (cur != nullptr) {
        // Рекурсивный вызов для левого поддерева
        printAllNodes(cur->left);
        // Вывод ключа и счетчика вершины
        std::cout << cur->key << " (" << cur->count << ")  ";
        // Рекурсивный вызов для правого поддерева
        printAllNodes(cur->right);
    }
}

// Функция поиска вершины по ключу
TreeNode *search(int searchKey) {
    // Устанавливаем текущую вершину в корень дерева
    pCur = root;
    // Пока не достигнут конец дерева
    while (pCur != nullptr) {
        if (pCur->key == searchKey) {
            // Если ключ найден, возвращаем указатель на вершину
            return pCur;
        } else if (pCur->key > searchKey) {
            // Если ключ меньше текущего, переходим в левое поддерево
            pCur = pCur->left;
        } else {
            // Иначе переходим в правое поддерево
            pCur = pCur->right;
        }
    }
    // Если ключ не найден, возвращаем nullptr
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
    if (root == nullptr) { // если дерево пустое
        root = new TreeNode(); // создаем корень дерева
        root->left = nullptr; // указываем, что левого потомка нет
        root->right = nullptr; // указываем, что правого потомка нет
        root->key = newKey; // устанавливаем ключ корня
        root->count = 1; // количество узлов в корне равно 1
        return;
    }

    TreeNode *cur = root; // указатель на текущий узел равен корню
    TreeNode *prev = nullptr; // указатель на предыдущий узел равен нулю

    while (cur != nullptr) { // пока текущий узел не нулевой
        prev = cur; // предыдущий узел равен текущему
        if (newKey < cur->key) { // если ключ меньше текущего, переходим к левому потомку
            cur = cur->left;
        } else if (newKey > cur->key) { // если ключ больше текущего, переходим к правому потомку
            cur = cur->right;
        } else { // Иначе, если ключ равен текущему
            cur->count++; // увеличиваем количество узлов в текущем узле
            return;
        }
    }

    auto *newNode = new TreeNode(); // создаем новый узел
    newNode->key = newKey; // устанавливаем ключ нового узла
    newNode->count = 1; // количество узлов в новом узле равно 1
    newNode->left = nullptr; // указываем, что левого потомка нет
    newNode->right = nullptr; // указываем, что правого потомка нет

    if (newKey < prev->key) { // если ключ меньше ключа предыдущего узла
        prev->left = newNode; // устанавливаем новый узел в качестве левого потомка предыдущего узла
    } else { // иначе, если ключ больше ключа предыдущего узла
        prev->right = newNode; // устанавливаем новый узел в качестве правого потомка предыдущего узла
    }
}

// Функция удаления вершины (ближайшая большая вершина)
void remove(TreeNode *&pRoot, int key) { // объявляем функцию удаления узла
    if (pRoot == nullptr) { // проверяем, была ли удалена вершина
        std::cout << "Вершина с ключом " << key << " не найдена в дереве.\n"; // выводим сообщение об ошибке
    } else {
        if (key < pRoot->key) { // если ключ удаляемого узла меньше ключа текущего узла
            remove(pRoot->left, key); // рекурсивно вызываем функцию удаления для левого поддерева
        } else if (key > pRoot->key) { // если ключ удаляемого узла больше ключа текущего узла
            remove(pRoot->right, key); // рекурсивно вызываем функцию удаления для правого поддерева
        } else { // если ключи совпадают
            if (pRoot->left == nullptr) { // если левое поддерево отсутствует
                TreeNode *temp = pRoot->right; // временный указатель на правое поддерево
                delete pRoot; // удаляем узел
                pRoot = temp; // текущий узел становится правым поддеревом
                std::cout << "\nВершина с ключом " << key << " удалена из дерева.\n";
            } else if (pRoot->right == nullptr) { // если правое поддерево отсутствует
                TreeNode *temp = pRoot->left; // временный указатель на левое поддерево
                delete pRoot; // удаляем узел
                pRoot = temp; // текущий узел становится левым поддеревом
                std::cout << "\nВершина с ключом " << key << " удалена из дерева.\n";
            } else { // если у удаляемого узла есть оба поддерева
                TreeNode *min = pRoot->right; // указатель на минимальный элемент в правом поддереве
                while (min->left != nullptr) { // ищем минимальный элемент в правом поддереве
                    min = min->left;
                }
                int minKey = min->key; // сохраняем значение ключа вершины-заменителя
                pRoot->key = minKey; // заменяем ключ удаляемого узла на ключ вершины-заменителя
                remove(pRoot->right, minKey); // рекурсивно вызываем функцию удаления для правого поддерева
                std::cout << "\nВершина с ключом " << key << " удалена из дерева.\n";
                std::cout << "Новая вершина-заменитель: " << minKey << std::endl;
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
