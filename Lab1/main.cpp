// Лабораторная работа №1 (раздел 1, тема 2, номер 4) - СТЕК НА ОСНОВЕ ДИНАМИЧЕСКОГО РАСПРЕДЕЛЕНИЯ ПАМЯТИ

#include <iostream>

// Описание стека
struct stack {
    int data;
    stack *next;
} *sp, *sp_second; // sp - указатель вершины главного стека, sp_second - вспомогательного

// Инициализация, создание пустого стека
inline void initStack() {
    sp = nullptr;
    sp_second = nullptr; // вспомогательный стек удаленных элементов
}

// Проверка пустоты стека
bool isEmpty() {
    if (sp == nullptr) {
        return true;
    } else {
        return false;
    }
}

// Проверка пустоты вспомогательного стека
bool isSecondEmpty() {
    if (sp_second == nullptr) {
        return true;
    } else {
        return false;
    }
}

// Функция вывода состояния главного стека
void showStack(stack *_sp) {
    if (_sp != nullptr) {
        std::cout << "\n";
        stack *current;
        current = _sp;
        int i = 1;
        do {
            std::cout << i << ") " << current->data << "\n";
            current = current->next;
            i++;
        } while (current != nullptr);
    } else {
        std::cout << "Стек пуст.\n";
    }
}

// Функция добавления в стек
stack *push(stack *_sp, int _value) {
    // Возвращает новую ссылку на head стека
    auto *item = new stack;
    item->data = _value;
    item->next = _sp;
    _sp = item;
    return _sp;
}

// Добавление с вершины вспомогательного стека
void addFromSecond() {
    stack *current = sp_second;
    sp_second = sp_second->next;
    current->next = sp;
    sp = current;
}

// Метод обработки ошибок ввода команды (проверяет, чтобы были введены ТОЛЬКО цифры, без букв)
int failure() {
    int a;
    while (!(std::cin >> a) || (std::cin.peek() != '\n')) {
        std::cin.clear();
        while (std::cin.get() != '\n');
        std::cout << "\nОШИБКА ВВОДА. ПОВТОРИТЕ ВВОД \n" << std::endl;
    }
    // cin.ignore(32767, '\n');
    return a;
}

// Функция добавления случайного числа элементов в стек
void pushRand() {
    int scount;
    std::cout << "Сколько чисел добавить? ";
    scount = failure();
    for (int i = 0; i < scount; i++) {
        sp = push(sp, rand());
    }
}

// Функция удаления из стека
int pop() {
    if (!isEmpty()) {
        int value = sp->data;
        stack *current;
        current = sp;
        sp = sp->next;
        delete current;
        return value;
    } else
        return -1;
}

// Вместо удаления - перемещение во вспомогательный стек
void moveToSecondStack() {
    stack *current = sp;
    sp = sp->next;
    current->next = sp_second;
    sp_second = current;
}


void menu() {
    int number, value, cmd;
    while (true) {
        std::cout << ".............................................................\n";
        std::cout << "\nВведите номер команды:\n";
        std::cout << "1. Вывести состояние главного стека\n";
        std::cout << "2. Добавить элемент в главный стек\n";
        std::cout << "3. Удалить элемент из главного стека\n";
        std::cout << "4. Добавить несколько случайных чисел в главный стек\n";
        std::cout << "5. Вывести состояние вспомогательного стека\n";
        std::cout << "0. Завершить работу программы\n";
        std::cout << "Ваш выбор:  ";
        number = failure(); // ввод номера команды

        if (number == 1) { // вывести состояние стека
            std::cout << "Состояние главного стека: ";
            showStack(sp);
        } else if (number == 2) { // добавить элемент в стек
            std::cout << "Уточните происхождение элемента: \n 1. Действительно создание нового элемента "
                         "\n 2. Выбор его с вершины вспомогательного стека\nВаш выбор: ";
            cmd = failure();
            if (cmd == 1) {
                std::cout << "Введите целое число: ";
                value = failure();
                sp = push(sp, value);
            } else if (cmd == 2) {
                if (!isSecondEmpty()) {
                    addFromSecond();
                } else std::cout << "Вспомогательный стек пуст.\n";
            } else
                std::cout << "Ошибка ввода. Повторите ввод команды\n";
        } else if (number == 3) { // удалить элемент из стека
            if (!isEmpty()) {
                std::cout << "Уточните команду: \n 1. Действительно удалить элемент с полным освобождением памяти "
                             "\n 2. Включить его в вершину вспомогательного стека удаленных элементов\nВаш выбор: ";
                cmd = failure();
                if (cmd == 1) {
                    value = pop();
                    if (value != -1) {
                        std::cout << "Элемент '" << value << "' удален\n";
                    } else {
                        std::cout << "Стек пуст.\n";
                    }
                } else if (cmd == 2) {
                    if (sp != nullptr) {
                        moveToSecondStack();
                    } else {
                        std::cout << "Стек пуст.\n";
                    }
                } else {
                    std::cout << "Ошибка ввода. Повторите ввод команды\n";
                }
            } else {
                std::cout << "Стек пуст. Удалять нечего\n";
            }
        } else if (number == 4) { // добавить несколько случайных чисел
            pushRand();
        } else if (number == 5) { // вывести состояние вспомогательного стека
            std::cout << "Состояние вспомогательного стека удаленных элементов: ";
            showStack(sp_second);
        } else if (number == 0) // завершить работу
            break;
        else
            std::cout << "Ошибка ввода. Повторите ввод команды\n";
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    initStack();
    srand(static_cast<unsigned int>(time(nullptr))); // инициализация генератора случайных чисел rand
    std::cout << "Генератор псевдослучайных чисел запущен\n";
    menu();
    return 0;
}