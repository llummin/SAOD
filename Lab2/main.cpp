//Лабораторная работа №2 (раздел 1, тема 2, номер 5) - КОЛЬЦЕВАЯ ОЧЕРЕДЬ НА ОСНОВЕ МАССИВА (СТАТИЧЕСКАЯ РЕАЛИЗАЦИЯ)
#include <iostream>

constexpr auto kMaxSize = 5;

struct queue {
    int front, rear;
    int array[kMaxSize];
};

// Инициализация очереди
void initQueue(queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Проверка очереди на пустоту
bool isEmpty(queue *q) {
    return (q->front == -1 && q->rear == -1);
}

// Проверка очереди на заполненность
bool isFull(queue *q) {
    return (q->rear + 1) % kMaxSize == q->front;
}

// Добавление элемента в конец очереди
void enqueue(queue *q, int x) {
    std::cout << "Добавлено " << x << " \n";
    if (isFull(q)) {
        std::cout << "Ошибка: Очередь заполнена\n";
        return;
    }
    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % kMaxSize;
    }
    q->array[q->rear] = x;
}

// Удаление элемента из начала очереди
void dequeue(queue *q) {
    std::cout << "Удалено \n";
    if (isEmpty(q)) {
        std::cout << "Ошибка: Очередь пуста\n";
        return;
    } else if (q->front == q->rear) {
        q->rear = q->front = -1;
    } else {
        q->front = (q->front + 1) % kMaxSize;
    }
}

// Вывод текущего состояния очереди
void printQueue(queue *q) {
    int count = (q->rear + kMaxSize - q->front) % kMaxSize + 1;
    std::cout << "Очередь: ";
    for (int i = 0; i < count; i++) {
        int index = (q->front + i) % kMaxSize;
        std::cout << q->array[index] << " ";
    }
    std::cout << "\n\n";
}

// Ввод целочисленного значения с проверкой
int failure() {
    int choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Введите данные правильно: ";
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
            std::cout << "Введите данные правильно: ";
            continue;
        }
        std::cin.ignore(32767, '\n');
        if (choice < begin || choice > end) {
            std::cout << "Введите данные правильно: ";
            continue;
        }
        break;
    }
    return choice;
}

// Основное меню
void callMenu(queue *q) {
    bool work{true};
    while (work) {
        std::cout << "...................................................\n";
        std::cout << "\nВведите номер команды:\n";
        std::cout << "1. Проверка пустоты очереди\n";
        std::cout << "2. Проверка заполненности очереди\n";
        std::cout << "3. Добавить элемент в конец очереди\n";
        std::cout << "4. Удалить элемент из начала очереди\n";
        std::cout << "5. Вывод текущего состояния очереди на экран\n";
        std::cout << "6. Завершить работу программы\n";
        std::cout << "Введите номер команды: ";

        int choice = failure(1, 6);
        switch (choice) {
            case 1:
                if (isEmpty(q)) {
                    std::cout << "Очередь пуста";
                } else {
                    std::cout << "Очередь не пуста";
                }
                std::cout << "\n\n";
                break;
            case 2:
                if (isFull(q)) {
                    std::cout << "Очередь полна";
                } else {
                    std::cout << "Очередь не полна";
                }
                std::cout << "\n\n";
                break;
            case 3:
                if (isFull(q)) {
                    std::cout << "Ошибка: Очередь полна!\n\n";
                    break;
                }
                std::cout << "Введите число для добавления в очередь: ";
                enqueue(q, failure());
                std::cout << "\n\n";
                break;
            case 4:
                dequeue(q);
                std::cout << "\n\n";
                break;
            case 5:
                printQueue(q);
                std::cout << "\n\n";
                break;
            case 6:
                work = false;
                std::cout << "\n\n";
                break;
            default:
                break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    auto *q = new queue;
    initQueue(q);
    callMenu(q);
    delete q;
}
