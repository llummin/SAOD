#include <iostream>

const int mTableSize = 5;
int count = 0;

struct KeyValueNode {
    KeyValueNode *next{};
    std::string key;
};

struct HashTableNode {
    std::string key;
    KeyValueNode *begin{};
    KeyValueNode *end{};
};

// Функция инициализации очереди
void initQueue(HashTableNode *hashTable[]) {
    for (int i = 0; i < mTableSize; i++) {
        hashTable[i] = new HashTableNode();
        hashTable[i]->key = "";
        hashTable[i]->begin = nullptr;
        hashTable[i]->end = nullptr;
    }
}

// Функция вычисления хэш-кода
int hashCode(const std::string &key) {
    int code = 0;
    for (char i: key) {
        code += static_cast<int>(i);
    }
    return code % mTableSize;
}

// Функция вывода хэш-таблицы в консоль
void printHashTable(HashTableNode **hashTable) {
    for (int i = 0; i < mTableSize; i++) {
        if (hashTable[i] == nullptr) {
            std::cout << "Индекс: " << i << ". Значение: пусто" << std::endl;
        } else {
            std::cout << "Индекс: " << i << ". Значение: " << hashTable[i]->key << " ";

            KeyValueNode *current = hashTable[i]->begin;
            while (current != nullptr) {
                std::cout << current->key << " ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    }
}

// Функция поиска ключа в хэш-таблице
int findKey(HashTableNode **hashTable, const std::string &key, int &counter) {
    KeyValueNode *current;
    counter = 0;
    int index = hashCode(key);
    counter++;
    if (hashTable[index]->key == key) {
        return index;
    }
    current = hashTable[index]->begin;
    while (current != nullptr) {
        counter++;
        if (current->key == key) {
            return index;
        }
        current = current->next;
    }
    return -1;
}

// Функция добавления ключа в хэш-таблицу
void insertKey(HashTableNode **hashTable, const std::string &key) {
    int counter = 0;
    KeyValueNode *temp;
    int index = hashCode(key);

    counter++;
    if ((hashTable[index]->key).empty()) {
        hashTable[index]->key = key;
        std::cout << "\nКлюч добавлен успешно. Число сравнений: " << counter << "\n";
        count++;
        return;
    }

    counter++;
    if (hashTable[index]->key == key) {
        std::cout << "\nДанный ключ уже находится в ячейке. Число сравнений: " << counter << "\n";
        return;
    }

    counter++;
    if (hashTable[index]->begin == nullptr) {
        hashTable[index]->begin = hashTable[index]->end = temp = new KeyValueNode();
        temp->key = key;
        temp->next = nullptr;
        std::cout << "\nКлюч добавлен успешно. Число сравнений: " << counter << "\n";
        count++;
    } else {
        temp = new KeyValueNode();
        temp->key = key;
        temp->next = nullptr;
        hashTable[index]->end->next = temp;
        std::cout << "\nКлюч добавлен успешно. Число сравнений: " << counter << "\n";
        count++;
    }
}

// Функция удаления ключа из хэш-таблицы
void removeKey(HashTableNode **hashTable, const std::string &key) {
    int index = hashCode(key);
    HashTableNode *currentCell = hashTable[index];

    if (currentCell->key == key) {
        if (currentCell->begin == nullptr) {
            currentCell->key = "";
        } else {
            currentCell->key = currentCell->begin->key;
            if (currentCell->end != currentCell->begin) {
                KeyValueNode *temp = currentCell->begin;
                currentCell->begin = currentCell->begin->next;
                delete temp;
            } else {
                delete currentCell->begin;
                currentCell->begin = currentCell->end = nullptr;
            }
        }
        count--;
        std::cout << "\nКлюч успешно удален\n";
        return;
    }

    KeyValueNode *curr = currentCell->begin;
    KeyValueNode *prev = nullptr;

    while (curr != nullptr && curr->key != key) {
        prev = curr;
        curr = curr->next;
    }

    if (curr != nullptr) {
        prev->next = curr->next;
        if (curr->next == nullptr) {
            currentCell->end = prev;
        }
        delete curr;
        count--;
        std::cout << "\nКлюч успешно удален\n";
    } else {
        std::cout << "\nКлюч не найден\n";
    }
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

// Ввод строки с проверкой на пустоту
std::string checkStringNotEmpty() {
    std::string str;
    bool is_space;
    while (true) {
        getline(std::cin, str);
        if (str.empty()) {
            std::cout << "Вы ввели пустую строку. Попробуйте еще раз: ";
        } else {
            is_space = true;
            for (char i: str) {
                if (!isspace(i)) {
                    is_space = false;
                    break;
                }
            }
            if (is_space) {
                std::cout << "Вы ввели пустую строку. Попробуйте еще раз: ";
            } else {
                return str;
            }
        }
    }
}

// Основное меню
void callMenu(HashTableNode **hashTable) {
    bool work = true;
    int choice;
    int service;
    int counter = 0;
    std::string key;

    while (work) {
        std::cout << "_______________________________________________________________________";
        std::cout << "\nВведите номер команды: \n";
        std::cout << "1. Вывести хеш-таблицу на экран\n";
        std::cout << "2. Добавить в хеш-таблицу ключ\n";
        std::cout << "3. Найти ключ в хеш-таблице\n";
        std::cout << "4. Удаление ключа\n";
        std::cout << "5. Завершение работы\n";
        std::cout << "_______________________________________________________________________\n";
        std::cout << "Введите номер команды: ";
        choice = failure(1, 5);
        switch (choice) {
            case 1:
                if (::count == 0) {
                    std::cout << "\nХеш-таблица пуста!" << std::endl;
                    break;
                }
                std::cout << "\nХэш-таблица: " << std::endl;
                printHashTable(hashTable);
                break;
            case 2:
                std::cout << "\nВведите ключ: ";
                key = checkStringNotEmpty();
                insertKey(hashTable, key);
                break;
            case 3:
                if (::count == 0) {
                    std::cout << "\nХеш-таблица пуста!" << std::endl;
                    break;
                }
                std::cout << "\nВведите ключ для поиска: ";
                key = checkStringNotEmpty();
                service = findKey(hashTable, key, counter);
                if (service == -1) {
                    std::cout << "\nДанного ключа в таблице нет. Число сравнений: " << counter << "\n";
                } else {
                    std::cout << "\nКлюч найден. Число сравнений: " << counter << "\n";
                }
                break;
            case 4:
                if (::count == 0) {
                    std::cout << "\nХеш-таблица пуста!" << std::endl;
                    break;
                }
                std::cout << "\nВведите ключ, который хотели бы удалить : ";
                key = checkStringNotEmpty();
                if (findKey(hashTable, key, counter) == -1) {
                    std::cout << "\nКлюч не найден\n";
                    break;
                }
                removeKey(hashTable, key);
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
    auto *hashTable = new HashTableNode *[mTableSize];
    initQueue(hashTable);
    callMenu(hashTable);
    delete[] hashTable;
}