// Раздел 2, тема 4, номер 3 - МЕТОД ОТКРЫТОГО ХЕШИРОВАНИЯ

#include <iostream>

const int mTableSize = 5; // Константа, определяющая размер хэш-таблицы
int count = 0; // Счетчик элементов в хэш-таблице

// Структура для узла с ключом и значением
struct KeyValueNode {
    KeyValueNode *next{}; // Указатель на следующий узел
    std::string key; // Ключ
};

// Структура для узла хэш-таблицы
struct HashTableNode {
    std::string key; // Ключ
    KeyValueNode *begin{}; // Указатель на начало списка узлов с ключами и значениями
    KeyValueNode *end{}; // Указатель на конец списка узлов с ключами и значениями
};

// Функция инициализации очереди (хэш-таблицы)
void initQueue(HashTableNode *hashTable[]) {
    for (int i = 0; i < mTableSize; i++) {
        hashTable[i] = new HashTableNode(); // Создание нового узла хэш-таблицы
        hashTable[i]->key = ""; // Инициализация ключа пустым значением
        hashTable[i]->begin = nullptr; // Инициализация начала списка узлов пустым значением
        hashTable[i]->end = nullptr; // Инициализация конца списка узлов пустым значением
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
    counter = 0; // Счетчик сравнений
    int index = hashCode(key); // Вычисление хэш-кода ключа
    counter++;
    if (hashTable[index]->key == key) { // Если ключ найден в самом узле хэш-таблицы
        return index;
    }
    current = hashTable[index]->begin;
    while (current != nullptr) { // Поиск ключа в списке узлов
        counter++;
        if (current->key == key) {
            return index;
        }
        current = current->next;
    }
    return -1; // Ключ не найден
}

// Функция добавления ключа в хэш-таблицу
void insertKey(HashTableNode **hashTable, const std::string &key) {
    int counter = 0; // Счетчик числа сравнений
    KeyValueNode *temp; // Временный указатель на узел
    int index = hashCode(key); // Вычисление хэш-кода ключа

    counter++;
    if ((hashTable[index]->key).empty()) { // Если ячейка хэш-таблицы пуста
        hashTable[index]->key = key; // Присваиваем ключу значение
        std::cout << "\nКлюч добавлен успешно. Число сравнений: " << counter << "\n";
        count++; // Увеличиваем счетчик элементов в хэш-таблице
        return;
    }

    counter++;
    if (hashTable[index]->key == key) { // Если ключ уже присутствует в ячейке
        std::cout << "\nДанный ключ уже находится в ячейке. Число сравнений: " << counter << "\n";
        return;
    }

    counter++;
    if (hashTable[index]->begin == nullptr) { // Если список узлов пуст
        hashTable[index]->begin = hashTable[index]->end = temp = new KeyValueNode(); // Создаем новый узел
        temp->key = key; // Присваиваем ключу значение
        temp->next = nullptr;
        std::cout << "\nКлюч добавлен успешно. Число сравнений: " << counter << "\n";
        count++; // Увеличиваем счетчик элементов в хэш-таблице
    } else { // Если список узлов не пуст
        temp = new KeyValueNode(); // Создаем новый узел
        temp->key = key; // Присваиваем ключу значение
        temp->next = nullptr;
        hashTable[index]->end->next = temp; // Связываем новый узел с последним узлом в списке
        std::cout << "\nКлюч добавлен успешно. Число сравнений: " << counter << "\n";
        count++; // Увеличиваем счетчик элементов в хэш-таблице
    }
}

// Функция удаления ключа из хэш-таблицы
void removeKey(HashTableNode **hashTable, const std::string &key) {
    int index = hashCode(key); // Вычисление хэш-кода ключа
    HashTableNode *currentCell = hashTable[index]; // Получение текущей ячейки хэш-таблицы

    if (currentCell->key == key) { // Если ключ найден в самом узле хэш-таблицы
        if (currentCell->begin == nullptr) { // Если список узлов пуст
            currentCell->key = ""; // Очищаем ключ
        } else {
            currentCell->key = currentCell->begin->key; // Заменяем ключ на ключ первого узла
            if (currentCell->end != currentCell->begin) { // Если в списке есть более одного узла
                KeyValueNode *temp = currentCell->begin;
                currentCell->begin = currentCell->begin->next; // Переустанавливаем начало списка
                delete temp; // Удаляем первый узел
            } else { // Если в списке только один узел
                delete currentCell->begin; // Удаляем первый и последний узел
                currentCell->begin = currentCell->end = nullptr;
            }
        }
        count--; // Уменьшаем счетчик элементов в хэш-таблице
        std::cout << "\nКлюч успешно удален\n";
        return;
    }

    KeyValueNode *curr = currentCell->begin; // Указатель на текущий узел
    KeyValueNode *prev = nullptr; // Указатель на предыдущий узел

    while (curr != nullptr && curr->key != key) { // Поиск ключа в списке узлов
        prev = curr;
        curr = curr->next;
    }

    if (curr != nullptr) { // Если ключ найден в списке узлов
        prev->next = curr->next; // Пропускаем текущий узел при связывании предыдущего и следующего узлов
        if (curr->next == nullptr) { // Если текущий узел - последний в списке
            currentCell->end = prev; // Обновляем указатель на конец списка
        }
        delete curr; // Удаляем текущий узел
        count--; // Уменьшаем счетчик элементов в хэш-таблице
        std::cout << "\nКлюч успешно удален\n";
    } else { // Если ключ не найден
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
    auto *hashTable = new HashTableNode *[mTableSize];
    initQueue(hashTable);
    callMenu(hashTable);
    delete[] hashTable;
}