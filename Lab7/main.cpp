// Лабораторная работа №7 (раздел 1, тема 3, номер 5) - ЛИНЕЙНЫЙ ДИНАМИЧЕСКИЙ ДВУНАПРАВЛЕННЫЙ СПИСОК

#include <iostream>

struct ListItem {
    int data;
    ListItem *next;
    ListItem *prev;
};

// Функция инициализации списка
void initList(ListItem *&head) {
    head = new ListItem;
    head->next = head;
    head->prev = head;
}

// Функция проверки списка на пустоту
bool isEmpty(ListItem *head) {
    return head->next == head;
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
void insertBefore(ListItem *&head) {
    auto *info = new ListItem;
    std::cout << "\nВведите значение элемента, перед которым нужно вставить новый: ";
    int pos = failure();
    ListItem *current = head->next;
    while (current != head) {
        if (current->data == pos) {
            break;
        }
        current = current->next;
    }
    if (current == head) {
        std::cout << "\nЭлемент не найден.\n";
    } else {
        std::cout << "\nВведите значение нового элемента: ";
        int elem = failure();
        info->data = elem;
        info->next = current;
        info->prev = current->prev;
        current->prev->next = info;
        current->prev = info;
    }
}

// Функция добавления нового элемента после заданного
void insertAfter(ListItem *&head) {
    auto *info = new ListItem;
    if (isEmpty(head)) {
        std::cout << "\nВведите значение нового элемента: ";
        int elem = failure();
        info->data = elem;
        info->next = head;
        info->prev = head;
        head->next = info;
        head->prev = info;
    } else {
        std::cout << "\nВведите значение элемента, после которого хотите вставить новый: ";
        int pos = failure();
        ListItem *current = head->next;
        while (current != head) {
            if (current->data == pos) {
                break;
            }
            current = current->next;
        }
        if (current == head) {
            std::cout << "\nЭлемент не найден!\n";
        } else {
            std::cout << "\nВведите значение нового элемента: ";
            int elem = failure();
            info->data = elem;
            info->next = current->next;
            info->prev = current;
            current->next->prev = info;
            current->next = info;
        }
    }
}

void searchForward(ListItem *head) {
    // TODO: Реализовать функцию поиска элемента в прямом направлении списка
}

void searchBackward(ListItem *head) {
    // TODO: Реализовать функцию поиска элемента в обратном направлении списка
}

void remove(ListItem *&head) {
    // TODO: Реализовать функцию для удаления элемента из списка
}

// Функция вывода списка на экран в прямом направлении
void printForward(ListItem *head) {
    if (isEmpty(head)) {
        std::cout << "Список пуст" << std::endl;
        return;
    }
    ListItem *cur = head->next;
    while (cur != head) {
        std::cout << cur->data << " ";
        cur = cur->next;
    }
    std::cout << std::endl;
}

// Функция вывода списка на экран в обратном направлении
void printBackward(ListItem *head) {
    if (isEmpty(head)) {
        std::cout << "Список пуст" << std::endl;
        return;
    }
    ListItem *cur = head->prev;
    while (cur != head) {
        std::cout << cur->data << " ";
        cur = cur->prev;
    }
    std::cout << std::endl;
}

// Основное меню
void callMenu(ListItem *head) {
    bool work{true};
    while (work) {
        std::cout << "\n...................................................\n";
        std::cout << "\nВведите номер команды: \n";
        std::cout << "1. Вывод списка в прямом направлении\n";
        std::cout << "2. Вывод списка в обратном направлении\n";
        std::cout << "3. Добавление нового элемента в список\n";
        std::cout << "4. Завершение работы программы\n";
        std::cout << "Введите номер команды: ";
        int choice = failure(1, 4);
        switch (choice) {
            case 1:
                if (isEmpty(head)) {
                    std::cout << "\nСписок пуст!";
                } else {
                    std::cout << "\nСписок в прямом направлении: ";
                    printForward(head);
                }
                break;
            case 2:
                if (isEmpty(head)) {
                    std::cout << "\nСписок пуст!";
                } else {
                    std::cout << "\nСписок в обратном направлении: ";
                    printBackward(head);
                }
                break;
            case 3:
                if (isEmpty(head))
                    insertAfter(head);
                else {
                    while (true) {
                        std::cout << "\nВыберите действие:\n";
                        std::cout << "1. Добавить новый элемент перед заданным.\n";
                        std::cout << "2. Добавить новый элемент после заданного.\n";
                        std::cout << "\nВаш вариант: ";
                        choice = failure();
                        if (choice == 1) {
                            insertBefore(head);
                            break;
                        } else if (choice == 2) {
                            insertAfter(head);
                            break;
                        }
                    }
                }
                break;
            case 4:
                work = false;
                std::cout << "\nПрограмма завершена...\n";
                break;
            default:
                break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    ListItem *head = nullptr;
    initList(head);
    callMenu(head);
}