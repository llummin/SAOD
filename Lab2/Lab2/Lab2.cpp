//Лабораторная работа №2 (раздел 1, тема 2, номер 5) - КОЛЬЦЕВАЯ ОЧЕРЕДЬ НА ОСНОВЕ МАССИВА (СТАТИЧЕСКАЯ РЕАЛИЗАЦИЯ)
#include <iostream>

using namespace std;

constexpr auto MAX_SIZE = 5;

struct Queue
{
    int Front, Rear;
    int Array[MAX_SIZE];
};

void InitQueue(Queue* q) // Инициализация очереди
{
	q->Front = -1;
	q->Rear = -1;
}

bool IsEmpty(Queue* q) // Проверка очереди на пустоту
{
	return (q->Front == -1 && q->Rear == -1); 
}

bool IsFull(Queue* q) // Проверка очереди на заполненность
{
	return (q->Rear + 1) % MAX_SIZE == q->Front ? true : false;
}

void Enqueue(Queue* q, int x) // Добавление элемента в конец очереди
{
	cout << "Добавлено " << x << " \n";
	if (IsFull(q))
	{
		cout << "Ошибка: Очередь заполнена\n";
		return;
	}
	if (IsEmpty(q))
	{
		q->Front = q->Rear = 0;
	}
	else
	{
		q->Rear = (q->Rear + 1) % MAX_SIZE;
	}
	q->Array[q->Rear] = x;
}

void Dequeue(Queue* q) // Удаление элемента из начала очереди
{
	cout << "Удалено \n";
	if (IsEmpty(q))
	{
		cout << "Ошибка: Очередь пуста\n";
		return;
	}
	else if (q->Front == q->Rear)
	{
		q->Rear = q->Front = -1;
	}
	else
	{
		q->Front = (q->Front + 1) % MAX_SIZE;
	}
}


void PrintQueue(Queue* q) // Вывод текущего состояния очереди
{
    int count = (q->Rear + MAX_SIZE - q->Front) % MAX_SIZE + 1;
    cout << "Очередь: ";
    for (int i = 0; i < count; i++)
    {
        int index = (q->Front + i) % MAX_SIZE; // Index of element while travesing circularly from front
        cout << q->Array[index] << " ";
    }
    cout << "\n\n";
}

int Failure() // Ввод целочисленного значения с проверкой
{
    int choice;
    while (true)
    {
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Введите данные правильно: ";
            continue;
        }
        cin.ignore(32767, '\n');
        break;
    }
    return choice;
}

int Failure(int begin, int end) // Ввод целочисленного значения с проверкой интервала
{
    int choice;
    while (true)
    {
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Введите данные правильно: ";
            continue;
        }
        cin.ignore(32767, '\n');
        if (choice < begin || choice > end)
        {
            cout << "Введите данные правильно: ";
            continue;
        }
        break;
    }
    return choice;
}

void CallMenu(Queue* q) // Основное меню
{
    bool work{ true };
    while (work)
    {
        cout << "___________________________________________________________\n";
        cout << "\nВведите номер команды:\n";
        cout << "1. Проверка пустоты очереди\n";
        cout << "2. Проверка заполненности очереди\n";
        cout << "3. Добавить элемент в конец очереди\n";
        cout << "4. Удалить элемент из начала очереди\n";
        cout << "5. Вывод текущего состояния очереди на экран\n";
        cout << "6. Завершить работу программы\n";
        cout << "Введите номер команды: ";

        int choice = Failure(1, 6);
        switch (choice)
        {
        case 1:
            if (IsEmpty(q))
            {
                cout << "Очередь пуста";
            }
            else
            {
                cout << "Очередь не пуста";
            }
            cout << "\n\n";
            break;
        case 2:
            if (IsFull(q))
            {
                cout << "Очередь полна";
            }
            else
            {
                cout << "Очередь не полна";
            }
            cout << "\n\n";
            break;
        case 3:
            if (IsFull(q))
            {
                cout << "Ошибка: Очередь полна!\n\n"; break;
            }
            cout << "Какое число хотите ввести в очередь?: ";
            Enqueue(q, Failure());
            cout << "\n\n";
            break;
        case 4:
            Dequeue(q);
            cout << "\n\n";
            break;
        case 5:
            PrintQueue(q);
            cout << "\n\n";
            break;
        case 6:
            work = false;
            cout << "\n\n";
            break;
        default:
            break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "RUS");
    Queue* q = new Queue;
    InitQueue(q);
    CallMenu(q);
    delete q;
}