// Раздел 2, тема 4, номер 1 - БЕСКОНФЛИКТНАЯ ХЕШ-ТАБЛИЦА

#include <iostream>
#include <string>

const int kArraySize = 10;

// Функция вычисления хэш-кода
int hash(const std::string &key) {
    int code = 0;
    for (char i: key) {
        code += (int) i;
    }
    return code % kArraySize;
}

// Функция создания хэш-таблицы на основе массива ключей
void createHashTable(std::string *&hashTable, std::string *keys) {
    for (int i = 0; i < kArraySize; i++) {
        hashTable[hash(keys[i])] = keys[i];
    }
}

// Функция вывода хэш-таблицы в консоль
void printHashTable(std::string *hashTable) {
    std::cout << "-----------------------" << std::endl;
    for (int i = 0; i < kArraySize; i++) {
        std::cout << "| " << i << " | " << hashTable[i] << std::endl;
        std::cout << "-----------------------" << std::endl;
    }
}

// Функция поиска ключа в хэш-таблице
int keySearch(const std::string &key, std::string *hashTable) {
    if (hashTable[hash(key)] == key) {
        return hash(key);
    }
    return -1;
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
void callMenu(std::string *&hashTable, std::string *keys) {
    bool work{true};
    int choice;
    while (work) {
        std::cout << "_______________________________________________________________________";
        std::cout << "\nВведите номер команды: \n";
        std::cout << "1. Заполнить хеш таблицу\n";
        std::cout << "2. Вывести хеш таблицу на экран\n";
        std::cout << "3. Найти ключ в хеш таблице\n";
        std::cout << "4. Завершение работы\n";
        std::cout << "_______________________________________________________________________\n";
        std::cout << "Введите номер команды: ";
        choice = failure(1, 4);
        switch (choice) {
            case 1:
                createHashTable(hashTable, keys);
                std::cout << "\nХеш-таблица заполнена!" << std::endl;
                break;
            case 2:
                if (!(hashTable[0].empty())) {
                    printHashTable(hashTable);
                } else {
                    std::cout << "\nХеш-таблица пуста!" << std::endl;
                }
                break;
            case 3:
                if (!(hashTable[0].empty())) {
                    std::cout << "Введите ключ для поиска: ";
                    std::string key = checkStringNotEmpty();
                    int index = keySearch(key, hashTable);
                    if (index == -1) {
                        std::cout << "\nТакого ключа нет!" << std::endl;
                    } else {
                        std::cout << "\nКлюч " << key << " в хеш таблице имеет место " << index << "." << std::endl;
                    }
                } else {
                    std::cout << "\nХеш-таблица пуста!" << std::endl;
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
    std::string keys[kArraySize] = {"WHILE", "AND", "RETURN", "STRUct", "OUT", "Ref",
                                    "FOREACH", "PROGRAM", "ARRAY", "Class"};
    auto *hashTable = new std::string[kArraySize]();
    callMenu(hashTable, keys);
}