// Раздел 1, тема 4, номер 1 - ЛИНЕЙНЫЙ ДИНАМИЧЕСКИЙ ДВУНАПРАВЛЕННЫЙ СПИСОК

#include <iostream>

struct ListItem {
    int data; // хранит значение элемента списка
    ListItem *next; // указатель на следующий элемент списка
    ListItem *prev; // указатель на предыдущий элемент списка
};

// Функция инициализации списка
void initList(ListItem *&head) {
    // Выделение памяти под головной элемент списка
    head = new ListItem;
    // Установка указателей следующего и предыдущего элементов головного элемента списка на самого себя
    head->next = head;
    head->prev = head;
}

// Функция проверки списка на пустоту
bool isEmpty(ListItem *head) {
    // Если указатель на следующий элемент головного элемента списка указывает на сам головной элемент, то список пустой
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
void insertBefore(ListItem *&head) { // принимаем ссылку на указатель на головной элемент списка
    auto *info = new ListItem; // создание нового элемента списка
    std::cout << "\nВведите значение элемента, перед которым нужно вставить новый: ";
    int pos = failure();
    // Начало поиска элемента списка с заданным значением, начиная с головного элемента
    ListItem *current = head->next;
    while (current != head) {
        if (current->data == pos) {
            break;
        }
        current = current->next;
    }
    // Если элемент не найден, вывод сообщения об ошибке
    if (current == head) {
        std::cout << "\nЭлемент не найден.\n";
    } else {
        std::cout << "\nВведите значение нового элемента: ";
        int elem = failure();
        // Заполнение информации о новом элементе списка
        info->data = elem;
        info->next = current;
        info->prev = current->prev;
        // Изменение указателя следующего элемента для предыдущего элемента текущего элемента
        current->prev->next = info;
        // Изменение указателя предыдущего элемента для текущего элемента
        current->prev = info;
    }
}

// Функция добавления нового элемента после заданного
void insertAfter(ListItem *&head) { // принимаем ссылку на указатель на головной элемент списка
    // Создание нового элемента списка
    auto *info = new ListItem;
    if (isEmpty(head)) {
        std::cout << "\nВведите значение нового элемента: ";
        int elem = failure();
        info->data = elem;  // присваивание новому элементу списка значения, введенного пользователем
        info->next = head;  // присваивание новому элементу указателя на следующий элемент списка
        info->prev = head;  // присваивание новому элементу указателя на предыдущий элемент списка
        head->next = info;  // изменение указателя на следующий элемент предыдущего элемента списка
        head->prev = info;  // изменение указателя на предыдущий элемент следующего элемента списка
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
            info->data = elem; // присваивание новому элементу списка значения, введенного пользователем
            info->next = current->next; // присваивание новому элементу указателя на следующий элемент списка
            info->prev = current; // присваивание новому элементу указателя на предыдущий элемент списка
            current->next->prev = info; // изменение указателя на предыдущий элемент следующего элемента списка
            current->next = info; // изменение указателя на следующий элемент заданного элемента списка
        }
    }
}

// Функция поиска элемента в прямом направлении списка
void searchForward(ListItem *head) { // принимаем ссылку на указатель на головной элемент списка
    if (isEmpty(head)) {
        std::cout << "\nСписок пуст! Поиск невозможен!\n";
        return;
    }

    std::cout << "\nВведите значение элемента, который нужно найти: ";
    int value = failure();

    ListItem *current = head->next; // установка указателя на первый элемент списка
    int index = 0;
    while (current != head) { // поиск элемента, пока не будет достигнут конец списка
        if (current->data == value) { // если элемент найден
            std::cout << "\nНайден элемент со значением " << current->data << " на позиции " << index << ".\n";
            return;
        }
        current = current->next; // переход к следующему элементу списка
        index++; // увеличиваем индекс текущего элемента
    }

    std::cout << "\nЭлемент со значением " << value << " не найден!\n";
}

// Функция поиска элемента в обратном направлении списка
void searchBackward(ListItem *head) { // принимаем ссылку на указатель на головной элемент списка
    if (isEmpty(head)) {
        std::cout << "\nСписок пуст! Поиск невозможен!\n";
        return;
    }

    std::cout << "\nВведите значение элемента, который нужно найти: ";
    int value = failure();

    ListItem *current = head->prev; // указатель на последний элемент списка
    int index = 0;
    while (current != head) { // итерация по списку до первого элемента
        if (current->data == value) { // если найден элемент со значением, равным искомому, то вывести сообщение
            std::cout << "\nНайден элемент со значением " << current->data << " на позиции " << index << ".\n";
            return;
        }
        current = current->prev; // переход к предыдущему элементу списка
        index++; // увеличиваем индекс текущего элемента
    }

    std::cout << "\nЭлемент со значением " << value << " не найден!\n";
}

// Функция удаления элемента по значению
void remove(ListItem *&head) { // принимаем ссылку на указатель на головной элемент списка
    if (isEmpty(head)) {
        std::cout << "\nСписок пуст! Удаление невозможно!\n";
        return;
    }

    std::cout << "\nВведите значение элемента, который нужно удалить: ";
    int pos = failure();  // запрашиваем значение элемента для удаления
    ListItem *current = head->next;  // текущий элемент - следующий за головным
    ListItem *prev = head;  // предыдущий элемент - головной

    while (current != head) {  // пока не дойдем до головного элемента списка
        if (current->data == pos) {  // если нашли элемент для удаления
            prev->next = current->next;  // пропускаем текущий элемент
            current->next->prev = prev;  // обновляем ссылку на предыдущий элемент у следующего за удаляемым
            delete current;  // удаляем текущий элемент
            std::cout << "\nЭлемент удален!\n";  // выводим сообщение об успешном удалении
            return;  // выходим из функции
        }
        prev = current;  // передвигаем указатель на предыдущий элемент
        current = current->next;  // передвигаем указатель на текущий элемент
    }
    std::cout << "\nЭлемент не найден!\n";
}

// Функция вывода списка на экран в прямом направлении
void printForward(ListItem *head) {
    if (isEmpty(head)) {
        std::cout << "Список пуст" << std::endl;
        return;
    }
    ListItem *cur = head->next; // инициализируем указатель на первый элемент списка
    while (cur != head) { // пока не дошли до конца списка
        std::cout << cur->data << " "; // выводим значение текущего элемента на экран
        cur = cur->next; // переходим к следующему элементу списка
    }
    std::cout << std::endl;
}

// Функция вывода списка на экран в обратном направлении
void printBackward(ListItem *head) {
    if (isEmpty(head)) {
        std::cout << "Список пуст" << std::endl;
        return;
    }
    ListItem *cur = head->prev; // инициализируем указатель на последний элемент списка
    while (cur != head) { // пока не дошли до конца списка
        std::cout << cur->data << " "; // выводим значение текущего элемента на экран
        cur = cur->prev; // переходим к предыдущему элементу списка
    }
    std::cout << std::endl;
}

// Основное меню
void callMenu(ListItem *head) {
    bool work{true};
    while (work) {
        std::cout << "_______________________________________________________________________";
        std::cout << "\nВведите номер команды: \n";
        std::cout << "1. Вывод списка в прямом направлении\n";
        std::cout << "2. Вывод списка в обратном направлении\n";
        std::cout << "3. Поиск элемента в прямом направлении списка\n";
        std::cout << "4. Поиск элемента в обратном направлении списка\n";
        std::cout << "5. Добавление нового элемента в список\n";
        std::cout << "6. Удаление элемента из списка\n";
        std::cout << "7. Завершение работы программы\n";
        std::cout << "_______________________________________________________________________\n";
        std::cout << "Введите номер команды: ";
        int choice = failure(1, 7);
        switch (choice) {
            case 1:
                if (isEmpty(head)) {
                    std::cout << "\nСписок пуст!\n";
                } else {
                    std::cout << "\nСписок в прямом направлении: ";
                    printForward(head);
                }
                break;
            case 2:
                if (isEmpty(head)) {
                    std::cout << "\nСписок пуст!\n";
                } else {
                    std::cout << "\nСписок в обратном направлении: ";
                    printBackward(head);
                }
                break;
            case 3:
                searchForward(head);
                break;
            case 4:
                searchBackward(head);
                break;
            case 5:
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
            case 6:
                remove(head);
                break;
            case 7:
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
