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
void printPostOrder(TreeNode *pRoot, int level) {
    if (pRoot != nullptr) {
        printPostOrder(pRoot->right, level + 1); // рекурсивно вызываем функцию для правой ветки

        // Вывод отступов пропорциональных уровню вершины
        for (int i = 0; i < level * 5; i++) { // цикл для вывода отступов перед значением вершины
            std::cout << " ";
        }

        std::cout << pRoot->key << std::endl; // выводим значение корневой вершины
        printPostOrder(pRoot->left, level + 1); // рекурсивно вызываем функцию для левой ветки
    }
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

// Основное меню
void callMenu() {
    bool work = true;
    int choice;
    while (work) {
        std::cout << "___________________________________________________________________________________";
        std::cout << "\nВарианты команд:\n";
        std::cout << "1. Построение дерева поиска с заданным числом вершин\n";
        std::cout << "2. Вывод дерева в обратно-симметричном порядке\n";
        std::cout << "3. Завершение работы\n";
        std::cout << "___________________________________________________________________________________\n";
        std::cout << "Введите номер команды: ";
        choice = failure(1, 3);
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
                printPostOrder(root, 0);
                break;
            case 3:
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
