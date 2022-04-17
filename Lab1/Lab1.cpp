//лаб.работа №1 (раздел 1, тема 2, номер 4) - СТЕК НА ОСНОВЕ ДИНАМИЧЕСКОГО РАСПРЕДЕЛЕНИЯ ПАМЯТИ

#include <iostream>

using namespace std;


//описание стека
struct stack {
    int data;
    stack* next;
} *sp, * sp_second; // sp - указатель вершины главного стека, sp_second - вспомогательного

//инициализация, создание пустого стека
inline void initstack() {
    sp = NULL;
    sp_second = NULL; //вспомогательный стек удаленных элементов
}

// Проверка пустоты стека
bool isEmpty() {
    if (sp == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

// Проверка пустоты вспомогательного стека
bool isSecondEmpty() {
    if (sp_second == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

//функция вывода состояния главного стека
void show_stack(stack* _sp) {
    if (_sp != NULL) {
        cout << "\n";
        stack* current;
        current = _sp;
        int i = 1;
        do {
            cout << i << ") " << current->data << "\n";
            current = current->next;
            i++;
        } while (current != NULL);
    }
    else {
        cout << "Стек пуст.\n";
    }
}

//функция добавления в стек
stack* push(stack* _sp, int _value) {
    //возвращает новую ссылку на head стека
    stack* item = new stack;
    item->data = _value;
    item->next = _sp;
    _sp = item;
    return _sp;
}

//добавление с вершины вспомогательного стека
void add_from_second() {
    stack* current = sp_second;
    sp_second = sp_second->next;
    current->next = sp;
    sp = current;
}

//метод обработки ошибок ввода команды (проверяет, чтобы были введены ТОЛЬКО цифры, без букв). возвращает ПРАВИЛЬНО ВВЕДЕННОЕ ЧИСЛО
int failure() {
    int a;
    while (!(cin >> a) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "\nОШИБКА ВВОДА. ПОВТОРИТЕ ВВОД \n" << endl;
    }
    //    cin.ignore(32767, '\n');
    return a;
}

//функция добавления рандомного числа элементов в стек
void PushRand() {
    int scount;
    cout << "Сколько чисел добавить? ";
    scount = failure();
    for (int i = 0; i < scount; i++)
        sp = push(sp, rand());
}

//функция удаления из стека
int pop() {
    if (!isEmpty()) {
        int value = sp->data;
        stack* current; current = sp;
        sp = sp->next;
        delete current;
        return value;
    }
    else
        return -1;
}

//вместо удаления - перемещение во вспомогательный стек
void move_to_second_stek() {
    stack* current = sp;
    sp = sp->next;
    current->next = sp_second;
    sp_second = current;
}


void menu() {
    int number, value, comd;
    while (true) {
        cout << ".............................................................\n";
        cout << "\nВведите номер команды:\n";
        cout << "1. Вывести состояние главного стека\n";
        cout << "2. Добавить элемент в главный стек\n";
        cout << "3. Удалить элемент из главного стека\n";
        cout << "4. Добавить несколько рандомных чисел в главный стек\n";
        cout << "5. Вывести состояние вспомогательного стека\n";
        cout << "0. Завершить работу программы\n";
        cout << "Ваш выбор: ";
        number = failure(); //ввод номера команды

        if (number == 1) { //Вывести состояние стека
            cout << "Состояние главного стека: ";
            show_stack(sp);
        }
        else if (number == 2) { //Добавить элемент в стек
            cout << "Уточните происхождение элемента: \n 1. Деиствительно создание нового элемента \n 2. Выбор его с вершины вспомогательного стека\nВаш Выбор: ";
            comd = failure();
            if (comd == 1) {
                cout << "Введите целое число: "; value = failure();
                sp = push(sp, value);
            }
            else if (comd == 2) {
                if (!isSecondEmpty()) add_from_second();
                else cout << "Вспомогательный стек пуст.\n";
            }
            else
                cout << "Ошибка ввода. Повторите ввод команды\n";
        }
        else if (number == 3) { //Удалить элемент из стека
            if (!isEmpty()) {
                cout << "Уточните команду: \n 1. Деиствительно удалить элемент с полным освобождением памяти \n 2. Включить его в вершину вспомогательного стека удаленных элементов\nВаш Выбор: ";
                comd = failure();
                if (comd == 1) {
                    value = pop();
                    if (value != -1) {
                        cout << "Элемент '" << value << "' удален\n";
                    }
                    else {
                        cout << "Стек пуст.\n";
                    }
                }
                else if (comd == 2) {
                    if (sp != NULL) {
                        move_to_second_stek();
                    }
                    else {
                        cout << "Стек пуст.\n";
                    }
                }
                else {
                    cout << "Ошибка ввода. Повторите ввод команды\n";
                }
            }
            else {
                cout << "Стек пуст. Удалять нечего\n";
            }
        }
        else if (number == 4)  //Добавить несколько рандомных чисел
            PushRand();
        else if (number == 5) { //Вывести состояние вспомогательного стека
            cout << "Состояние вспомогательного стека удаленных элементов: ";
            show_stack(sp_second);
        }
        else if (number == 0) //Завершить работу
            break;
        else
            cout << "Ошибка ввода. Повторите ввод команды\n";
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    initstack();
    srand(static_cast<unsigned int>(time(0))); //srand(time(NULL)); //инициализация генератора случайных чисел rand
    cout << "Генератор псевдослучаиных чисел запущен\n";
    menu();
    return 0;
}

