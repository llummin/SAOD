// Раздел 1, тема 3, номер 5 - ЛИНЕЙНЫЙ ДИНАМИЧЕСКИЙ СПИСОК С УДАЛЕНИЕМ ЭЛЕМЕНТОВ ВО 2-Й СПИСОК

#include <iostream>

struct ListItem {
    int data;
    ListItem *next;
};

// Функция инициализации списков
void initList(ListItem *&head, ListItem *&stackHead) {
    // Создание заголовка основного списка
    head = new ListItem;
    head->next = nullptr; // устанавливает указатель на следующий элемент главного списка равным nullptr.

    // Создание заголовка вспомогательного списка
    stackHead = new ListItem;
    stackHead->next = nullptr; // устанавливает указатель на следующий элемент вспомогательного списка равным nullptr.
}

// Функция проверки списка на пустоту
bool isEmpty(ListItem *head) {
    return head->next == nullptr; // если список пустой (т.е. указатель на следующий элемент списка равен nullptr)
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
void insertBefore(ListItem *head) {
    // Выделение памяти для нового объекта ListItem
    auto *info = new ListItem;
    std::cout << "\nВведите значение элемента, перед которым нужно вставить новый: ";
    int pos = failure();
    ListItem *current = head->next; // получение указателя на первый элемент списка
    ListItem *prev = head; // получение указателя на заголовок списка
    while (current != nullptr) { // поиск элемента списка, перед которым нужно вставить новый
        if (current->data == pos) {
            break;
        }
        prev = current;
        current = current->next;
    }
    if (current == nullptr) {
        std::cout << "\nЭлемент не найден.\n";
    } else {
        std::cout << "\nВведите значение нового элемента: ";
        int elem = failure();
        info->data = elem; // заполняем информацию нового элемента
        info->next = current; // устанавливаем связь между новым элементом и элементом, перед которым он будет вставлен
        prev->next = info; // устанавливаем связь между предыдущим элементом и новым элементом
        std::cout << "\nДобавлен элемент " << elem << "\n";
    }
}


// Функция добавления нового элемента после заданного
void insertAfter(ListItem *head) {
    // Выделение памяти для нового объекта ListItem
    auto *info = new ListItem;
    if (isEmpty(head)) {
        std::cout << "\nВведите значение нового элемента: ";
        int elem = failure();
        info->data = elem;
        info->next = nullptr;
        head->next = info;
        std::cout << "\nДобавлен элемент " << elem << "\n";
    } else {
        std::cout << "\nВведите значение элемента, после которого хотите вставить новый: ";
        int pos = failure();
        ListItem *current = head->next;

        // Находим элемент в списке, после которого следует добавить новый элемент.
        while (current != nullptr) {
            if (current->data == pos) {
                break;
            }
            current = current->next;
        }
        if (current == nullptr) {
            std::cout << "\nЭлемент не найден!\n";
        } else {
            std::cout << "\nВведите значение нового элемента: ";
            int elem = failure();
            info->data = elem;
            info->next = current->next;
            current->next = info;
            std::cout << "\nДобавлен элемент " << elem << "\n";
        }
    }
}

// Функция поиска элемента по значению
int search(ListItem *head) {
    if (isEmpty(head)) {
        std::cout << "\nГлавный список пуст. Поиск невозможен!\n";
        return -1;
    }
    std::cout << "\nВведите значение элемента для поиска: ";
    int elem = failure();
    ListItem *current = head->next; // устанавливаем указатель на первый элемент в списке.
    int index = 0; // инициализируем переменную для хранения индекса найденного элемента.
    while (current != nullptr) { // проверяем, не дошли ли мы до конца списка.
        if (current->data == elem) { // проверяем, равно ли значение текущего элемента искомому значению.
            std::cout << "\nИндекс искомого элемента: " << index << std::endl;
            return index;
        }
        current = current->next; // переходим к следующему элементу в списке.
        index++; // увеличиваем индекс текущего элемента на 1.
    }
    std::cout << "\nЭлемент не найден\n";
    return -1;
}

// Функция удаления элемента по значению и занесение его во вспомогательный список
void remove(ListItem *head, ListItem *stackHead) {
    if (isEmpty(head)) {
        std::cout << "\nГлавный список пуст! Удаление невозможно!" << std::endl;
        return;
    }

    // Запрос значения элемента, который нужно удалить
    std::cout << "\nВведите значение элемента, который нужно удалить: ";
    int elem = failure();

    // Инициализация указателей на текущий элемент и предыдущий элемент
    ListItem *current = head->next;
    ListItem *prev = head;

    // Поиск элемента по заданному значению
    while (current != nullptr) {
        if (current->data == elem) {
            prev->next = current->next; // удаление элемента из главного списка
            current->next = stackHead->next; // добавление элемента во вспомогательный список
            stackHead->next = current;
            std::cout << "\nЭлемент " << elem << " удален из главного списка и добавлен во вспомогательный\n";
            return;
        }
        prev = current; // обновление указателя prev на элемент, предшествующий current
        current = current->next; // обновление указателя current на следующий элемент в главном списке
    }
    std::cout << "\nЭлемент не найден.\n";
}

// Функция для отображения текущего состояния списка
void printList(ListItem *head) {
    if (isEmpty(head)) {
        std::cout << "\nВспомогательный список пуст!" << std::endl;
    } else {
        // Объявление указателя на текущий элемент списка и присвоение ему ссылки на следующий элемент после head.
        ListItem *current = head->next;
        while (current != nullptr) { // цикл, который продолжается, пока текущий элемент не станет равным nullptr.
            std::cout << current->data << " ";
            current = current->next; // перемещение указателя на следующий элемент списка.
        }
        std::cout << std::endl;
    }
}

// Основное меню
void callMenu(ListItem *head, ListItem *stackHead) {
    bool work{true};
    while (work) {
        std::cout << "___________________________________________________________";
        std::cout << "\nВведите номер команды: \n";
        std::cout << "1. Вывести текущее состояние главного списка\n";
        std::cout << "2. Вывести текущее состояние вспомогательного списка\n";
        std::cout << "3. Добавить элемент в главный список\n";
        std::cout << "4. Удаление элемента из главного списка\n";
        std::cout << "5. Поиск элемента в главном списке\n";
        std::cout << "6. Завершить работу программы\n";
        std::cout << "___________________________________________________________\n";
        std::cout << "Введите номер команды: ";

        int choice = failure(1, 6);
        switch (choice) {
            case 1:
                if (isEmpty(head)) {
                    std::cout << "\nГлавный список пуст!\n";
                } else {
                    std::cout << "\nГлавный список: ";
                    printList(head);
                }
                break;
            case 2:
                if (!isEmpty(stackHead)) {
                    std::cout << "\nВспомогательный список: ";
                }
                printList(stackHead);
                break;
            case 3:
                if (isEmpty(head)) {
                    insertAfter(head);
                } else {
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
                remove(head, stackHead);
                break;
            case 5:
                search(head);
                break;
            case 6:
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
    ListItem *head = nullptr;
    ListItem *stackHead = nullptr;
    initList(head, stackHead);
    callMenu(head, stackHead);
}