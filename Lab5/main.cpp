// Лабораторная работа №5 (раздел 1, тема 3, номер 3) - ЛИНЕЙНЫЙ СПИСОК НА БАЗЕ МАССИВА С УКАЗАТЕЛЯМИ - ИНДЕКСАМИ

#include <iostream>

const int kMaxSize = 3;

struct ListItem {
    int data;
    int next;
};

struct List {
    ListItem array[kMaxSize];
    int count;
};


// Функция инициализации списка
void initList(List *my_list) {
    my_list->array[0].next = 0;
    my_list->count = 0;
    for (int i = 1; i < kMaxSize; i++) {
        my_list->array[i].next = -1; // отметить ячейку как свободную
    }
}

// Функция проверки списка на пустоту
bool isEmpty(List *my_list) {
    // Если список пуст, то номер первого элемента списка в заголовке должен быть равен 0
    return my_list->array[0].next == 0;
}

// Функция проверки списка на полноту
bool isFull(List *my_list) {
    if (my_list->count == kMaxSize) {
        return true;
    } else {
        return false;
    }
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

// Функция добавления нового элемента перед заданным
void insertBefore(List *my_list) {
    if (isFull(my_list)) {
        std::cout << "\nCписок полон! Добавление невозможно!\n";
    } else {
        std::cout << "\nВведите значение элемента, перед которым нужно вставить новый: ";
        int pos = failure();
        int current = my_list->array[0].next;
        int prev = 0;
        while (current != 0) {
            if (my_list->array[current].data == pos) {
                break;
            }
            prev = current;
            current = my_list->array[current].next;
        }
        if (current == 0) {
            std::cout << "\nЭлемент не найден.\n";
        } else {
            int temp = 1;
            while (my_list->array[temp].next != -1) {
                temp++;
            }
            std::cout << "\nВведите значение нового элемента: ";
            int elem = failure();
            my_list->array[temp].data = elem;
            my_list->array[temp].next = current;
            if (prev == 0) {
                my_list->array[0].next = temp;
            } else {
                my_list->array[prev].next = temp;
            }
            my_list->count++;
        }
    }
}

// Функция добавления нового элемента после заданного
void insertAfter(List *my_list) {
    if (isFull(my_list))
        std::cout << "\nCписок полон! Добавление невозможно!\n";
    else {
        if (isEmpty(my_list)) {
            int temp = 1;
            std::cout << "\nВведите значение нового элемента: ";
            int elem = failure();
            my_list->array[temp].data = elem;
            my_list->array[temp].next = 0;
            my_list->array[0].next = temp;
            my_list->count++;
        } else {
            std::cout << "\nВведите значение элемента, после которого хотите вставить новый: ";
            int pos = failure();
            int current = my_list->array[0].next;
            while (current != 0) {
                if (my_list->array[current].data == pos) {
                    break;
                }
                current = my_list->array[current].next;
            }
            if (current == 0) {
                std::cout << "\nЭлемент не найден!\n";
            } else {
                int temp = 1;
                while (my_list->array[temp].next != -1) {
                    temp++;
                }
                std::cout << "\nВведите значение нового элемента: ";
                int elem = failure();
                my_list->array[temp].data = elem;
                my_list->array[temp].next = my_list->array[current].next;
                my_list->array[current].next = temp;
                my_list->count++;
            }
        }
    }
}

// Функция поиска элемента по значению
int search(List *my_list) {
    if (isEmpty(my_list)) {
        std::cout << "\nСписок пуст. Поиск невозможен!\n";
        return -1;
    }
    std::cout << "\nВведите значение элемента для поиска: ";
    int elem = failure();
    int current = my_list->array[0].next;
    int index = -1;
    for (int i = 0; i < my_list->count; i++) {
        if (my_list->array[current].data == elem) {
            index = i;
        }
        current = my_list->array[current].next;
    }
    if (index == -1) {
        std::cout << "\nЭлемент не найден\n";
    } else {
        std::cout << "\nИндекс искомого элемента: " << index << std::endl;
    }
    return index;
}

// Функция удаления элемента по значению из списка
void remove(List *my_list, int value) {
    if (isEmpty(my_list)) {
        std::cout << "\nСписок пуст. Удаление невозможно!\n";
        return;
    }

    int current = my_list->array[0].next;
    int prev = 0;
    bool found = false;

    while (current != 0) {
        if (my_list->array[current].data == value) {
            found = true;
            break;
        }
        prev = current;
        current = my_list->array[current].next;
    }

    if (!found) {
        std::cout << "\nЭлемент не найден\n";
        return;
    }

    my_list->array[prev].next = my_list->array[current].next;
    my_list->array[current].next = -1;
    my_list->count--;
}

// Функция для отображения текущего состояния списка
void printList(List *my_list) {
    if (isEmpty(my_list)) {
        std::cout << "\nСписок пуст!" << std::endl;
        return;
    }
    int current = my_list->array[0].next;
    while (current != 0) {
        std::cout << my_list->array[current].data << " ";
        current = my_list->array[current].next;
    }
    std::cout << std::endl;
}


// Основное меню
void callMenu(List *my_list) {
    bool work{true};
    while (work) {
        std::cout << "\n...................................................\n";
        std::cout << "\nВведите номер команды: \n";
        std::cout << "1. Вывести текущее состояние списка\n";
        std::cout << "2. Добавить элемент в список\n";
        std::cout << "3. Удаление элемента из списка\n";
        std::cout << "4. Поиск элемента\n";
        std::cout << "5. Завершить работу программы\n";
        std::cout << "Введите номер команды: ";
        int choice = failure(1, 5);
        switch (choice) {
            case 1:
                if (isEmpty(my_list)) {
                    std::cout << "\nСписок пуст!";
                } else {
                    std::cout << "\nСписок: ";
                    printList(my_list);
                }
                break;
            case 2:
                if (isEmpty(my_list))
                    insertAfter(my_list);
                else {
                    while (true) {
                        std::cout << "\nВыберите действие:\n";
                        std::cout << "1. Добавить новый элемент перед заданным.\n";
                        std::cout << "2. Добавить новый элемент после заданного.\n";
                        std::cout << "\nВаш вариант: ";
                        choice = failure();
                        if (choice == 1) {
                            insertBefore(my_list);
                            break;
                        } else if (choice == 2) {
                            insertAfter(my_list);
                            break;
                        }
                    }
                }
                break;
            case 3:
                if (isEmpty(my_list)) {
                    std::cout << "\nСписок пуст\n";
                    break;
                }
                int remove_value;
                std::cout << "\nВведите значение элемента, который вы хотите удалить: ";
                remove_value = failure();
                remove(my_list, remove_value);
                std::cout << "\n";
                break;
            case 4:
                search(my_list);
                break;
            case 5:
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
    List *my_list = new List;
    initList(my_list);
    callMenu(my_list);
    delete my_list;
    return 0;
}