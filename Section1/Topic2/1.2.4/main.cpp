// Раздел 1, тема 2, номер 4 - СТЕК НА ОСНОВЕ ДИНАМИЧЕСКОГО РАСПРЕДЕЛЕНИЯ ПАМЯТИ

#include <iostream>

// Описание стека
struct Stack {
    int data;
    Stack *next;
} *sp, *sp_second; // sp - указатель вершины главного стека, sp_second - вспомогательного

// Инициализация, создание пустого стека
inline void initStack() {
    sp = nullptr;
    sp_second = nullptr; // вспомогательный стек удаленных элементов
}

// Проверка пустоты стека
bool isEmpty() {
    return sp == nullptr;
}

// Проверка пустоты вспомогательного стека
bool isSecondEmpty() {
    return sp_second == nullptr;
}

// Функция вывода состояния главного стека
void showStack(Stack *_sp) {
    if (_sp != nullptr) {
        std::cout << "\n";
        Stack *current;
        current = _sp;
        int i = 1;
        do {
            std::cout << i << ") " << current->data << "\n";
            current = current->next;
            i++;
        } while (current != nullptr);
    } else {
        std::cout << "пусто...\n";
    }
}

// Функция добавления в стек
Stack *push(Stack *_sp, int _value) {
    // Возвращает новую ссылку на head стека
    auto *item = new Stack;
    item->data = _value;
    item->next = _sp;
    _sp = item;
    return _sp;
}

// Добавление с вершины вспомогательного стека
void addFromSecond() {
    Stack *current = sp_second;
    sp_second = sp_second->next;
    current->next = sp;
    sp = current;
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

// Функция добавления случайного числа элементов в стек
void pushRand() {
    int scount;
    scount = failure();
    for (int i = 0; i < scount; i++) {
        sp = push(sp, rand());
    }
}

// Функция удаления из стека
int pop() {
    if (!isEmpty()) {
        int value = sp->data;
        Stack *current;
        current = sp;
        sp = sp->next;
        delete current;
        return value;
    } else {
        return -1;
    }
}

// Функция удаления - перемещения во вспомогательный стек
void moveToSecondStack() {
    Stack *current = sp;
    sp = sp->next;
    current->next = sp_second;
    sp_second = current;
}

void callMenu() {
    bool work{true};
    int value, cmd;
    while (work) {
        std::cout << "______________________________________________________________";
        std::cout << "\nВарианты команд:\n";
        std::cout << "1. Вывести состояние главного стека\n";
        std::cout << "2. Добавить элемент в главный стек\n";
        std::cout << "3. Удалить элемент из главного стека\n";
        std::cout << "4. Добавить несколько случайных чисел в главный стек\n";
        std::cout << "5. Вывести состояние вспомогательного стека\n";
        std::cout << "6. Завершить работу программы\n";
        std::cout << "______________________________________________________________\n";
        std::cout << "Ваш выбор:  ";
        int number = failure(1, 6);
        switch (number) {
            case 1:
                std::cout << "\nСостояние главного стека: ";
                showStack(sp);
                break;
            case 2:
                std::cout << "\nУточните происхождение элемента: \n";
                std::cout << "1. Действительно создание нового элемента \n";
                std::cout << "2. Выбор его с вершины вспомогательного стека\n";
                std::cout << "Ваш выбор:  ";
                cmd = failure();
                switch (cmd) {
                    case 1:
                        std::cout << "\nВведите целое число: ";
                        value = failure();
                        sp = push(sp, value);
                        break;
                    case 2:
                        if (!isSecondEmpty()) {
                            addFromSecond();
                        } else {
                            std::cout << "\nВспомогательный стек пуст.\n";
                        }
                        break;
                    default:
                        std::cout << "\nОшибка ввода. Повторите ввод команды\n";
                        break;
                }
                break;
            case 3:
                if (!isEmpty()) {
                    std::cout << "\nУточните команду: \n";
                    std::cout << "1. Действительно удалить элемент с полным освобождением памяти \n";
                    std::cout << "2. Включить его в вершину вспомогательного стека удаленных элементов\n";
                    std::cout << "Ваш выбор: ";
                    cmd = failure();
                    switch (cmd) {
                        case 1:
                            value = pop();
                            if (value != -1) {
                                std::cout << "\nЭлемент '" << value << "' удален\n";
                            } else {
                                std::cout << "\nСтек пуст.\n";
                            }
                            break;
                        case 2:
                            if (sp != nullptr) {
                                moveToSecondStack();
                            } else {
                                std::cout << "\nСтек пуст.\n";
                            }
                            break;
                        default:
                            std::cout << "\nОшибка ввода. Повторите ввод команды\n";
                            break;
                    }
                } else {
                    std::cout << "\nСтек пуст. Удалять нечего\n";
                }
                break;
            case 4:
                std::cout << "\nВведите количество случайных чисел: ";
                pushRand();
                break;
            case 5:
                std::cout << "\nСостояние вспомогательного стека: ";
                showStack(sp_second);
                break;
            case 6:
                work = false;
                std::cout << "\nПрограмма завершена....";
                break;
            default:
                std::cout << "\nОшибка ввода. Повторите ввод команды\n";
                break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    initStack();
    srand(static_cast<unsigned int>(time(nullptr)));
    callMenu();
}
