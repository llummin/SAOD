// Лабораторная работа №3 (раздел 1, тема 2, номер 7) - ОЧЕРЕДЬ СО СЛУЧАЙНЫМ ЧИСЛОМ ДОБАВЛЯЕМЫХ И УДАЛЯЕМЫХ ЭЛЕМЕНТОВ

#include <iostream>

struct queueElement {
    char data;
    queueElement *next;
};

// Функция инициализации очереди
void initQueue(queueElement** begin, queueElement** end) {
    *begin = new queueElement; // выделение памяти для первого элемента в очереди
    (*begin)->next = nullptr; // установка следующего указателя первого элемента в значение nullptr
    *end = *begin;           // установка указателей begin и end так, чтобы они указывали на первый элемент
}

// Функция проверки пустоты очереди
bool isQueueEmpty(queueElement* begin) {
    return (begin->next == nullptr); // если следующий указатель первого элемента равен nullptr, то очередь пуста
}

// Функция добавления элемента в очередь
void enqueue(queueElement** end, char data) {
    auto *newElement = new queueElement;  // создаем новый элемент
    newElement->data = data;             // записываем данные в новый элемент
    newElement->next = nullptr;         // указываем, что следующий элемент отсутствует
    (*end)->next = newElement;         // предыдущий элемент теперь указывает на новый элемент
    *end = newElement;                // обновляем указатель на конец очереди
}

// Функция удаления элемента из очереди
void dequeue(queueElement** begin) {
    if (!isQueueEmpty(*begin)) {
        queueElement *temp = (*begin)->next;
        (*begin)->next = temp->next;
        delete temp;
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    queueElement *begin = nullptr;
    queueElement *end = nullptr;
    initQueue(&begin, &end);
    enqueue(&end, 'A');
    enqueue(&end, 'B');
    enqueue(&end, 'C');
    std::cout << "Элементы очереди: ";
    while (!isQueueEmpty(begin)) {
        std::cout << begin->next->data << " ";
        dequeue(&begin);
    }
    std::cout << std::endl;
    return 0;
}