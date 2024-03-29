// Раздел 1, тема 3, номер 2 - УПОРЯДОЧЕННЫЙ ЛИНЕЙНЫЙ СПИСОК НА ОСНОВЕ МАССИВА

#include <iostream>

const int kMaxSize = 5; // максимальный размер массива

struct ArrayList {
    int count; // текущее количество элементов в массиве
    int array[kMaxSize]; // массив элементов
};

// Функция инициализации списка
void initList(ArrayList *&my_list) {
    my_list->count = 0;
    // Обнуляем все элементы массива
    for (int &i: my_list->array) {
        i = 0;
    }
}

// Функция проверки пустоты списка
bool isEmpty(ArrayList *my_list) {
    return my_list->count == 0;
}

// Функция проверки полноты списка
bool isFull(ArrayList *my_list) {
    return my_list->count == kMaxSize;
}

// Функция добавления элемента в упорядоченный список
void insert(ArrayList *my_list, int item) {
    // Проверяем, есть ли место для добавления нового элемента
    if (isFull(my_list)) {
        // Если список полон, выводим сообщение об ошибке и прерываем выполнение функции
        std::cout << "Список полон. Не удаётся добавить новый элемент." << std::endl;
        return;
    }

    int i;
    // Ищем место для вставки нового элемента в упорядоченный список
    for (i = 0; i < my_list->count; i++) {
        if (my_list->array[i] > item) {
            // Нашли правильное место для вставки элемента, сдвигаем все элементы на одну позицию вправо
            for (int j = my_list->count - 1; j >= i; j--) {
                my_list->array[j + 1] = my_list->array[j];
            }
            // Вставляем элемент на его место
            my_list->array[i] = item;
            my_list->count++;
            return;
        }
    }

    // Если элемент должен быть добавлен в конец списка
    my_list->array[i] = item;
    my_list->count++;
}

// Функция удаления элемента по его значению
void remove(ArrayList *my_list, int value) {
    int i = 0;
    while (i < my_list->count && my_list->array[i] != value) {
        i++; // находим первый элемент, который равен значению
    }
    if (i < my_list->count && my_list->array[i] == value) { // проверяем, существует ли элемент с заданным значением
        std::cout << "\nУдален элемент со значением " << value << "\n";
        while (i < my_list->count - 1) {
            my_list->array[i] = my_list->array[i + 1];
            i++;
        }
        my_list->array[my_list->count - 1] = 0; // удаляем последний элемент
        my_list->count--; // уменьшаем количество элементов в списке
    } else {
        std::cout << "\nЭлемент со значением " << value << " не найден. Удаление невозможно!\n";
    }
}

// Функция для поиска элемента с заданной информационной частью
int search(ArrayList *my_list, int value) {
    for (int i = 0; i < my_list->count; i++) { // проходим по всем элементам списка
        if (my_list->array[i] == value) { // если нашли элемент со значением value
            return i;  // возвращаем индекс найденного элемента
        }
    }
    return -1;  // элемент не найден
}

// Функция для отображения текущего состояния списка
void printList(ArrayList *my_list) {
    for (int i = 0; i < my_list->count; i++) { // проходим по всем элементам списка
        std::cout << my_list->array[i] << " ";  // выводим значение каждого элемента списка
    }
    std::cout << std::endl; // переходим на новую строку
}

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


// Основное меню
void callMenu(ArrayList *my_list) {
    bool work{true};
    while (work) {
        std::cout << "________________________________________________";
        std::cout << "\nВарианты команд:\n";
        std::cout << "1. Вывести текущее состояние списка\n";
        std::cout << "2. Добавить элемент в список\n";
        std::cout << "3. Удаление элемента по значению\n";
        std::cout << "4. Поиск элемента\n";
        std::cout << "5. Завершить работу программы\n";
        std::cout << "________________________________________________\n";
        std::cout << "Введите номер команды: ";

        int choice = failure(1, 5);
        switch (choice) {
            case 1:
                if (isEmpty(my_list)) {
                    std::cout << "\nСписок пуст\n";
                } else {
                    std::cout << "\nСписок: ";
                    printList(my_list);
                }
                std::cout << "\n";
                break;
            case 2:
                if (isFull(my_list)) {
                    std::cout << "\nСписок заполнен\n";
                    break;
                }
                std::cout << "\nВведите число, которое хотите добавить: ";
                insert(my_list, failure());
                std::cout << "\n";
                break;
            case 3:
                if (isEmpty(my_list)) {
                    std::cout << "\nСписок пуст. Удаление невозможно!\n";
                    break;
                }
                int remove_value;
                std::cout << "\nВведите значение элемента, который вы хотите удалить: ";
                remove_value = failure();
                remove(my_list, remove_value);
                std::cout << "\n";
                break;
            case 4:
                if (isEmpty(my_list)) {
                    std::cout << "\nСписок пуст. Поиск невозможен!\n";
                    break;
                }
                int value_index;
                std::cout << "\nВведите информационную часть элемента, индекс которого вы хотите найти: ";
                value_index = search(my_list, failure());
                if (value_index == -1) {
                    std::cout << "\nЭлемент не найден\n";
                } else {
                    std::cout << "\nЭлемент найден, его индекс: " << value_index << "\n";
                }
                break;
            case 5:
                work = false;
                std::cout << "\n";
                break;
            default:
                break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    auto *my_list = new ArrayList;
    initList(my_list);
    callMenu(my_list);
    delete my_list;
    return 0;
}