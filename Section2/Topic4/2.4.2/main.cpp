#include <iostream>
#include <string>

const int mTableSize = 11;
int count = 0;

// Функция вычисления хэш-кода
int hash(const std::string &key) {
    int code = 0;
    for (char i: key) {
        code += static_cast<int>(i);
    }
    return code % mTableSize;
}

// Функция добавления ключа в хэш-таблицу
void insertKey(std::string hashTable[], const std::string &key, int &compares) {
    int index = hash(key);
    compares++;
    if (hashTable[index].empty()) {
        hashTable[index] = key;
        count++;
    } else {
        if (key == hashTable[index]) {
            return;
        } else {
            for (int i = 0; i < mTableSize - 2; i++) {
                int j = ((index + i) % mTableSize) + 1;
                if (j == mTableSize) {
                    j = 0;
                }
                compares++;
                if (hashTable[j].empty()) {
                    hashTable[j] = key;
                    count++;
                    break;
                }
            }
        }
    }
}

// Функция поиска ключа в хэш-таблице
int findKey(std::string hashTable[], const std::string &key, int &compares) {
    int index = hash(key);
    compares++;
    if (hashTable[index].empty()) {
        return -1;
    } else {
        if (key == hashTable[index]) {
            return index;
        } else {
            for (int i = 0; i < mTableSize - 2; i++) {
                int j = ((index + i) % mTableSize) + 1;
                if (j == mTableSize) {
                    j = 0;
                }
                compares++;
                if (hashTable[j] == key) {
                    return j;
                }
            }
            return -1;
        }
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

// Основное меню
void callMenu(std::string *&hashTable, std::string *keys) {
    bool work{true};
    int choice;
    while (work) {
        std::cout << "_______________________________________________________________________";
        std::cout << "\nВведите номер команды: \n";
        std::cout << "1. Заполнить хеш-таблицу исходными ключами\n";
        std::cout << "2. Добавить в хеш-таблицу ключ\n";
        std::cout << "3. Вывести хеш-таблицу на экран\n";
        std::cout << "4. Найти ключ в хеш-таблице\n";
        std::cout << "5. Завершение работы\n";
        std::cout << "_______________________________________________________________________\n";
        std::cout << "Введите номер команды: ";
        choice = failure(1, 4);
        switch (choice) {
            case 1: {
                if (count == mTableSize) {
                    std::cout << "\nХеш-таблица заполнена. Добавление невозможно!\n";
                } else {
                    int compares = 0;
                    for (int i = 0; i < mTableSize; i++) {
                        insertKey(hashTable, keys[i], compares);
                    }
                    std::cout << "\nХеш-таблица успешно заполнена\n";
                }
                break;
            }
            case 2: {
                if (count == mTableSize) {
                    std::cout << "\nХеш-таблица заполнена. Добавление невозможно!\n";
                } else {
                    int compares = 0;
                    std::cout << "\nВведите ключ: ";
                    std::string key;
                    std::cin >> key;
                    if (!key.empty()) {
                        int index = findKey(hashTable, key, compares);
                        if (index == -1) {
                            insertKey(hashTable, key, compares);
                            std::cout << "\nКлюч добавлен. Количество сравнений: " << compares << "\n";
                        } else {
                            std::cout << "\nТакой ключ уже есть!\n";
                        }
                    }
                }
                break;
            }
            case 3: {
                for (int i = 0; i < mTableSize; i++) {
                    if (hashTable[i].empty()) {
                        std::cout << "\nИндекс массива: " << i << " - Значение: пусто\n";
                    } else {
                        std::cout << "\nИндекс массива: " << i << " - Значение: " << hashTable[i] << "\n";
                    }
                }
                break;
            }
            case 4: {
                int compares = 0;
                std::cout << "\nВведите ключ: ";
                std::string key;
                std::cin >> key;
                int index = findKey(hashTable, key, compares);
                if (index == -1) {
                    std::cout << "\nКлюч не найден\n";
                } else {
                    std::cout << "\nКлюч найден. Индекс в массиве: " << index << "\n";
                    std::cout << "\nКоличество сравнений: " << compares << "\n";
                }
                break;
            }
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
    std::string keys[mTableSize] = {"ИВАНОВ", "СМИРНОВ", "КУЗНЕЦОВ", "ПОПОВ", "СОКОЛОВ",
                                    "ЛЕБЕДЕВ", "КОЗЛОВ", "НОВИКОВ", "МОРОЗОВ", "ПЕТРОВ"};
    auto *hashTable = new std::string[mTableSize]();
    callMenu(hashTable, keys);
    delete[] hashTable;
    return 0;
}