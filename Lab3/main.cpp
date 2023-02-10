// Лабораторная работа №3 (раздел 1, тема 2, номер 7) - ОЧЕРЕДЬ СО СЛУЧАЙНЫМ ЧИСЛОМ ДОБАВЛЯЕМЫХ И УДАЛЯЕМЫХ ЭЛЕМЕНТОВ

#include <iostream>
#include <conio.h>

struct queueElement {
    char data;
    queueElement *next;
};

// Функция инициализации очереди
void initQueue(queueElement **begin, queueElement **end) {
    *begin = new queueElement; // выделение памяти для первого элемента в очереди
    (*begin)->next = nullptr; // установка следующего указателя первого элемента в значение nullptr
    *end = *begin;           // установка указателей begin и end так, чтобы они указывали на первый элемент
}

// Функция проверки пустоты очереди
bool isQueueEmpty(queueElement *q) {
    return (q->next == nullptr);
}

// Функция добавления элемента в очередь
void enqueue(queueElement **end, char data) {
    auto *newElement = new queueElement;  // создаем новый элемент
    newElement->data = data;             // записываем данные в новый элемент
    newElement->next = nullptr;         // указываем, что следующий элемент отсутствует
    (*end)->next = newElement;         // предыдущий элемент теперь указывает на новый элемент
    *end = newElement;                // обновляем указатель на конец очереди
}

// Функция удаления элемента из очереди
void dequeue(queueElement **begin, queueElement **end) {
    if (!isQueueEmpty(*begin)) {           // проверяем, что очередь не пуста
        queueElement *temp = (*begin)->next; // сохраняем адрес следующего элемента в очереди
        (*begin)->next = temp->next;        // изменяем указатель next первого элемента на указатель след. элемента
        if (isQueueEmpty(*begin)) {     // если следующий элемент пуст, значит в очереди остался только один элемент
            *end = *begin;                // поэтому конец очереди теперь должен указывать на начало очереди
        }
        delete temp;    // освобождение памяти, которую занимает удаленный элемент
    }
}

// Вывод текущего состояния очереди
void printQueue(queueElement *begin) {
    if (isQueueEmpty(begin)) {            // проверяем, что очередь не пуста
        std::cout << "Пусто";               // если пуста, выводим соответствующее сообщение
    }
    queueElement *temp = begin->next;     // временный указатель, указывающий на следующий элемент в очереди
    while (temp != nullptr) {            // пока указатель не указывает на nullptr
        std::cout << temp->data << " "; // выводим данные текущего элемента
        temp = temp->next;             // переходим к следующему
    }
    std::cout << std::endl;         // переход на новую строку после вывода всех элементов
}

// Очищение памяти
void clearQueue(queueElement *begin) {
    queueElement *q = begin;     // создание указателя на первый элемент в очереди
    while (begin != nullptr) {  // цикл для итерации по всем элементам очереди
        begin = begin->next;   // переход к следующему элементу в очереди
        delete q;             // удаление текущего элемента
        q = begin;           // переназначение указателя `q` для перехода к следующему элементу
    }
}

// Работа очереди со случайными элементами
void queueWork(queueElement *begin, queueElement *end) {
    bool work = true;
    int operation_num = 1;
    while (true) {
        int timeBegin = clock();
        while (clock() - timeBegin < 600) {
            if (_kbhit() && (_getch() == 'q')) { // реагирует на нажатие клавиши 'q'
                work = false;
                break;
            }
        }
        if (!work) {
            clearQueue(begin);
            break;
        }
        std::cout << operation_num << ") Операция: ";
        int choice = (rand() % 99 + 1) % 2;
        int amount = rand() % 3 + 1;
        if (choice == 0) {
            std::cout << "Добавление ";
            for (int i = 0; i < amount; i++) {
                char letter = rand() % 26 + 65;
                enqueue(&end, letter);
            }
        } else {
            std::cout << "Удаление ";
            for (int i = 0; i < amount; i++) {
                dequeue(&begin, &end);
            }
        }
        std::cout << amount << " элементов(-а)\n";
        std::cout << "Текущая очередь: ";
        printQueue(begin);
        std::cout << "\n\n";
        operation_num++;
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    srand(time(nullptr));
    std::cout << "Работа очереди запущена ...\n";
    queueElement *begin;
    queueElement *end;
    initQueue(&begin, &end);
    queueWork(begin, end);
    return 0;
}