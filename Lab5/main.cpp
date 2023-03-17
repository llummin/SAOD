// Лабораторная работа №5 (раздел 1, тема 3, номер 3) - ЛИНЕЙНЫЙ СПИСОК НА БАЗЕ МАССИВА С УКАЗАТЕЛЯМИ - ИНДЕКСАМИ

#include <iostream>

const int kMaxSize = 3; // максимальный размер списка

struct ListItem {
    int data; // данные элемента
    int next; // индекс следующего элемента списка
};

struct List {
    ListItem array[kMaxSize]; // массив элементов списка
    int count; // количество элементов в списке
};

// Функция инициализации списка
void initList(List *my_list) {
    my_list->array[0].next = 0; // номер первого элемента списка равен 0
    my_list->count = 0; // список пуст
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
    return my_list->count == kMaxSize - 1;
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
    if (isFull(my_list)) { // если список полон, то выводим сообщение о невозможности добавления нового элемента
        std::cout << "\nCписок полон! Добавление невозможно!\n";
    } else {
        std::cout << "\nВведите значение элемента, перед которым нужно вставить новый: ";
        int pos = failure(); // получаем значение элемента, перед которым нужно вставить новый
        int current = my_list->array[0].next; // начинаем обход списка с первого элемента
        int prev = 0; // запоминаем предыдущий элемент
        // ищем место для вставки
        while (current != 0) {
            if (my_list->array[current].data == pos) { // если нашли нужный элемент, то выходим из цикла
                break;
            }
            prev = current; // запоминаем текущий элемент, как предыдущий
            current = my_list->array[current].next; // переходим к следующему элементу
        }
        if (current == 0) { // если не нашли элемент, перед которым нужно вставить новый
            std::cout << "\nЭлемент не найден.\n"; // выводим сообщение об ошибке
        } else { // иначе вставляем новый элемент
            int temp = 1;
            while (my_list->array[temp].next != -1) { // ищем пустое место для записи нового элемента
                temp++; // увеличение индекса
            }
            std::cout << "\nВведите значение нового элемента: ";
            int elem = failure();
            my_list->array[temp].data = elem;  // записываем значение в пустой элемент
            my_list->array[temp].next = current; // присваиваем ссылку на следующий элемент
            if (prev == 0) { // если элемент, перед которым нужно вставить новый, первый в списке
                my_list->array[0].next = temp; // обновляем ссылку на первый элемент
            } else { // иначе обновляем ссылку на предыдущий элемент
                my_list->array[prev].next = temp;
            }
            my_list->count++; // увеличиваем счетчик элементов списка
            std::cout << "\nДобавлен элемент " << elem << ".\n";
        }
    }
}

// Функция добавления нового элемента после заданного
void insertAfter(List *my_list) {
    if (isFull(my_list)) { // если список полон, то выводим сообщение о невозможности добавления нового элемента
        std::cout << "\nCписок полон! Добавление невозможно!\n";
    } else {
        if (isEmpty(my_list)) {
            int temp = 1;
            std::cout << "\nВведите значение нового элемента: ";
            int elem = failure();
            my_list->array[temp].data = elem; // записываем значение нового элемента в поле data
            my_list->array[temp].next = 0; // записываем значение 0 в поле next структуры элемента списка с индексом temp
            my_list->array[0].next = temp; // записываем значение temp в поле next структуры элемента списка с индексом 0
            my_list->count++; // увеличиваем счетчик количества элементов списка на 1
            std::cout << "\nДобавлен элемент " << elem << ".\n";
        } else {
            std::cout << "\nВведите значение элемента, после которого хотите вставить новый: ";
            int pos = failure();
            int current = my_list->array[0].next; // временная переменная current принимает значение поля next
            while (current != 0) {
                if (my_list->array[current].data == pos) {
                    break;
                }
                current = my_list->array[current].next; // присваиваем current значение поля next
            }
            if (current == 0) {
                std::cout << "\nЭлемент не найден!\n";
            } else {
                int temp = 1;
                while (my_list->array[temp].next != -1) { // ищем пустое место для записи нового элемента
                    temp++;
                }
                std::cout << "\nВведите значение нового элемента: ";
                int elem = failure();
                my_list->array[temp].data = elem; // записываем значение нового элемента в поле data
                // присваиваем значение поля next нового элемента - следующий элемент после заданного элемента
                my_list->array[temp].next = my_list->array[current].next;
                // присваиваем значение поля next заданного элемента - индекс добавленного элемента
                my_list->array[current].next = temp;
                my_list->count++; // увеличиваем счетчик количества элементов списка на 1
                std::cout << "\nДобавлен элемент " << elem << ".\n";
            }
        }
    }
}

// Функция удаления элемента по значению из списка
void remove(List *my_list, int value) {
    if (isEmpty(my_list)) {
        std::cout << "\nСписок пуст\n";
        return;
    }

    int current = my_list->array[0].next; // начинаем обход с первого элемента
    int prev = 0; // запоминаем предыдущий элемент
    bool found = false; // флаг, найден ли элемент

    while (current != 0) { // пока не достигнут конец списка
        if (my_list->array[current].data == value) { // если элемент найден
            found = true;
            break;
        }
        prev = current; // запоминаем текущий элемент как предыдущий
        current = my_list->array[current].next; // переходим к следующему элементу
    }

    if (!found) {
        std::cout << "\nЭлемент не найден\n";
        return;
    }

    my_list->array[prev].next = my_list->array[current].next; // удаляем найденный элемент из списка
    my_list->array[current].next = -1; // помечаем его как удаленный
    my_list->count--; // уменьшаем счетчик элементов в списке
    std::cout << "\nУдален элемент: " << value; // выводим сообщение об удалении элемента
}

// Функция поиска элемента по значению
int search(List *my_list) {

    std::cout << "\nВведите значение элемента для поиска: ";
    int elem = failure();
    int current = my_list->array[0].next; // временная переменная current принимает значение поля next
    int index = -1;
    // Ищем элемент в списке
    for (int i = 0; i < my_list->count; i++) {
        if (my_list->array[current].data == elem) {
            index = i;
        }
        current = my_list->array[current].next;
    }

    // Если элемент не найден, выводим сообщение об этом
    if (index == -1) {
        std::cout << "\nЭлемент не найден\n";
    } else { // иначе выводим индекс найденного элемента
        std::cout << "\nИндекс искомого элемента: " << index << std::endl;
    }
    return index;
}

// Функция для отображения текущего состояния списка
void printList(List *my_list) {
    if (isEmpty(my_list)) {
        std::cout << "\nСписок пуст!" << std::endl;
        return;
    }
    int current = my_list->array[0].next; // временная переменная current принимает значение поля next
    // Выводим все элементы списка
    while (current != 0) {
        std::cout << my_list->array[current].data << " ";
        current = my_list->array[current].next; // присваиваем current значение поля next
    }
    std::cout << std::endl;
}


// Основное меню
void callMenu(List *my_list) {
    bool work{true};
    while (work) {
        std::cout << "________________________________________________";
        std::cout << "\nВведите номер команды: \n";
        std::cout << "1. Вывести текущее состояние списка\n";
        std::cout << "2. Добавить элемент в список\n";
        std::cout << "3. Удаление элемента из списка\n";
        std::cout << "4. Поиск элемента\n";
        std::cout << "5. Завершить работу программы\n";
        std::cout << "________________________________________________\n";
        std::cout << "Введите номер команды: ";

        int choice = failure(1, 5);
        switch (choice) {
            case 1:
                if (isEmpty(my_list)) {
                    std::cout << "\nСписок пуст!\n";
                } else {
                    std::cout << "\nСписок: ";
                    printList(my_list);
                }
                break;
            case 2:
                if (isEmpty(my_list)) {
                    insertAfter(my_list);
                } else {
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