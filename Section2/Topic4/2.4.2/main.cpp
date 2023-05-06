// Раздел 2, тема 4, номер 2 - МЕТОД ЗАКРЫТОГО ХЕШИРОВАНИЯ

#include <iostream>
#include <string>

const int mTableSize = 10;
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
    int index = hash(key);  // Вычисляем индекс для вставки ключа
    compares++;  // Увеличиваем счетчик сравнений
    if (hashTable[index].empty()) {  // Если ячейка таблицы пуста
        hashTable[index] = key;  // Вставляем ключ
        count++;  // Увеличиваем счетчик элементов в таблице
    } else {  // Иначе производим линейное пробирование
        if (key == hashTable[index]) {  // Если ключ уже существует в таблице
            return;  // Прекращаем вставку
        } else {  // Если ячейка занята другим ключом
            for (int i = 0; i < mTableSize - 2; i++) {
                int j = ((index + i) % mTableSize) + 1;  // Вычисляем следующий индекс с помощью циклического сдвига
                if (j == mTableSize) {
                    j = 0;  // Если достигнут конец таблицы, переходим в начало
                }
                compares++;  // Увеличиваем счетчик сравнений
                if (hashTable[j].empty()) {  // Если ячейка пуста
                    hashTable[j] = key;  // Вставляем ключ
                    count++;  // Увеличиваем счетчик элементов в таблице
                    break;  // Прекращаем пробирование
                }
            }
        }
    }
}

// Функция поиска ключа в хэш-таблице
int findKey(std::string hashTable[], const std::string &key, int &compares) {
    int index = hash(key);  // Вычисляем индекс для поиска ключа
    compares++;  // Увеличиваем счетчик сравнений
    if (hashTable[index].empty()) {  // Если ячейка таблицы пуста
        return -1;  // Ключ не найден
    } else {
        if (key == hashTable[index]) {  // Если ключ найден в первоначальной ячейке
            return index;  // Возвращаем индекс ячейки
        } else {  // Иначе производим линейное пробирование
            for (int i = 0; i < mTableSize - 2; i++) {
                int j = ((index + i) % mTableSize) + 1;  // Вычисляем следующий индекс с помощью циклического сдвига
                if (j == mTableSize) {
                    j = 0;  // Если достигнут конец таблицы, переходим в начало
                }
                compares++;  // Увеличиваем счетчик сравнений
                if (hashTable[j] == key) {  // Если ключ найден в ячейке
                    return j;  // Возвращаем индекс ячейки
                }
            }
            return -1;  // Ключ не найден
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
void callMenu(std::string *&hashTable) {
    bool work{true};
    int choice;
    while (work) {
        std::cout << "_______________________________________________________________________";
        std::cout << "\nВведите номер команды: \n";
        std::cout << "1. Добавить в хеш-таблицу ключ\n";
        std::cout << "2. Вывести хеш-таблицу на экран\n";
        std::cout << "3. Найти ключ в хеш-таблице\n";
        std::cout << "4. Завершение работы\n";
        std::cout << "_______________________________________________________________________\n";
        std::cout << "Введите номер команды: ";
        choice = failure(1, 4);
        switch (choice) {
            case 1: {
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
            case 2: {
                for (int i = 0; i < mTableSize; i++) {
                    if (hashTable[i].empty()) {
                        std::cout << "\nИндекс массива: " << i << " - Значение: пусто\n";
                    } else {
                        std::cout << "\nИндекс массива: " << i << " - Значение: " << hashTable[i] << "\n";
                    }
                }
                break;
            }
            case 3: {
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
    auto *hashTable = new std::string[mTableSize]();
    callMenu(hashTable);
    delete[] hashTable;
    return 0;
}