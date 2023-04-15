// Раздел 2, тема 3 - СПЕЦИАЛЬНЫЕ МЕТОДЫ СОРТИРОВКИ

#include <iostream>
#include <random>

const int kMaxSize = 10000;

struct ListItem {
    int data; // поле данных
    ListItem *next; // указатель на следующий элемент
};

// Функция создания массива с уникальными ключами
void createUniqueArray(int *arr, int size) {
    for (int i = 0; i < size; i++) { // цикл по всем элементам массива
        arr[i] = i; // присваиваем очередному элементу массива значение i
    }
    // Перемешиваем элементы массива в случайном порядке
    shuffle(arr, arr + size, std::mt19937(std::random_device()()));
}

// Функция вывода массива
void printArray(const int *data, int size) {
    for (int i = 0; i < size; i++) { // цикл по всем элементам массива
        std::cout << data[i] << " "; // выводим очередной элемент массива на экран
    }
    std::cout << "\n"; // переходим на новую строку
}

// Функция выполнения простейшей карманной сортировки с использованием второго массива
void simpleBucketSort(int *data, int size, int &swaps) {
    swaps = 0; // обнуляем количество перестановок
    int maxVal = *std::max_element(data, data + size); // находим максимальное значение в массиве
    int *bucket = new int[maxVal + 1](); // создаем массив карманов и заполняем его нулями
    for (int i = 0; i < size; i++) { // цикл по всем элементам массива
        bucket[data[i]]++; // увеличиваем значение соответствующего кармана
        swaps++; // увеличиваем количество перестановок
    }
    int index = 0; // объявляем переменную для индекса текущего элемента в исходном массиве
    for (int i = 0; i <= maxVal; i++) { // цикл по всем карманам
        for (int j = 0; j < bucket[i]; j++) { // цикл по всем элементам в кармане
            data[index] = i; // записываем значение кармана в исходный массив
            index++; // увеличиваем индекс текущего элемента в исходном массиве
            swaps++; // увеличиваем количество перестановок
        }
    }
    std::cout << std::endl << "Отсортированный массив:\n";
    printArray(data, size); // вызываем функцию для вывода массива на экран
    std::cout << "\nКоличество перестановок: " << swaps << std::endl;
    delete[] bucket; // освобождаем память, выделенную под массив карманов
}

// Функция выполнения простейшей карманной сортировки без использования второго массива
void simpleBucketSortNoBucket(int *data, int size, int &compares, int &swaps) {
    compares = 0; // инициализация количества сравнений
    swaps = 0; // инициализация количества перестановок
    int temp; // объявление временной переменной
    for (int i = 0; i < size; i++) { // цикл сортировки
        temp = data[i]; // временная переменная равна текущему элементу
        while (temp != i) { // пока временная переменная не равна текущему индексу
            swaps++; // увеличение количества перестановок
            compares++; // увеличение количества сравнений
            data[i] = data[temp]; // текущий элемент равен элементу с индексом temp
            data[temp] = temp; // элемент с индексом temp равен временной переменной
            temp = data[i]; // временная переменная равна текущему элементу
        }
        compares++; // увеличение количества сравнений
    }
    std::cout << std::endl << "Отсортированный массив:\n";
    printArray(data, size); // вызов функции вывода массива на экран
    std::cout << "\nКоличество перестановок: " << swaps << std::endl;
    std::cout << "Количество сравнений: " << compares << std::endl;
}

// Функция добавления элемента в связный список
void addItem(ListItem *pItem, int value) {
    auto *pNew = new ListItem; // создание нового элемента списка
    pNew->data = value; // присвоение полю data значение value
    pNew->next = nullptr; // указатель на следующий элемент равен nullptr
    while (pItem->next != nullptr) { // пока указатель на следующий элемент не равен nullptr
        pItem = pItem->next; // переход к следующему элементу списка
    }
    pItem->next = pNew; // присвоение указателю на следующий элемент значение pNew
}

// Функция очищения списка
void clearList(ListItem *head) {
    while (head != nullptr) { // пока голова списка не равна nullptr
        ListItem *temp = head; // временная переменная равна голове списка
        head = head->next; // голова списка равна следующему элементу
        delete temp; // удаление временной переменной
    }
}

// Функция отсортированного массива при помощи обобщенной карманной сортировки
void showBucket(ListItem *data, int n) {
    std::cout << "\nОтсортированный массив:" << std::endl;
    for (int i = 0; i < n; i++) { // цикл по всем элементам массива
        ListItem *current = data[i].next; // указатель на первый элемент в списке, начинающемся с i-го элемента массива
        while (current != nullptr) { // цикл до тех пор, пока не достигнут конец списка
            std::cout << current->data << " "; // вывод данных текущего элемента
            current = current->next; // переход к следующему элементу списка
        }
    }
    std::cout << std::endl;
}

// Функция выполнения обобщенной карманной сортировки
void bucketSort(int *data, int size, int &swaps) {
    swaps = 0; // обнуление счетчика перестановок
    auto *sortedArray = new ListItem[size]; // создание динамического массива структур
    for (int i = 0; i < size; i++) { // цикл по всем элементам массива
        sortedArray[i].next = nullptr; // инициализация указателя на следующий элемент
    }
    // Цикл по всем элементам массива, увеличение счетчика перестановок на каждой итерации
    for (int i = 0; i < size; i++, swaps++) {
        addItem(&sortedArray[data[i]], data[i]); // добавление элемента в список с помощью функции addItem
    }
    showBucket(sortedArray, size); // вывод отсортированного массива на экран
    std::cout << "\nКоличество перестановок: " << swaps << std::endl;
    for (int i = 0; i < size; i++) { // цикл по всем элементам массива
        clearList(sortedArray[i].next); // очистка списка
    }
    delete[] sortedArray;
}

// Функция выполнения поразрядной сортировки
void radixSort(int *data, int size, int &swaps) {
    int max = 0; // объявление переменной максимального значения
    for (int i = 0; i < size; i++) { // цикл по всем элементам массива
        if (data[i] > max) // если текущий элемент больше максимального
            max = data[i]; // обновляем максимальное значение
    }

    auto *sortedArray = new ListItem[10]; // создание динамического массива из 10 элементов структуры ListItem
    int i = 0; // объявление переменной-счетчика
    int div = 1; // значение делителя
    swaps = 0; // счетчик перестановок

    while (max / div > 0) { // цикл, работающий до тех пор, пока максимальное значение не будет меньше делителя
        i++; // увеличение значения счетчика
        for (int j = 0; j < 10; j++) // цикл по всем элементам динамического массива
            sortedArray[j].next = nullptr; // обнуление указателей на следующие элементы списка

        // Распределение элементов в списки
        for (int j = 0; j < size; j++) { // цикл по всем элементам массива
            int digit = (data[j] / div) % 10; // вычисление цифры числа, соответствующей текущему разряду
            addItem(&sortedArray[digit], data[j]); // добавление элемента в соответствующий список
            swaps++; // увеличение счетчика перестановок
        }

        // Сборка элементов из списков
        int index = 0; // объявление переменной-счетчика
        for (int j = 0; j < 10; j++) { // цикл по всем элементам динамического массива
            ListItem *tmp = sortedArray[j].next; // объявление временного указателя на следующий элемент списка
            while (tmp != nullptr) { // цикл, работающий до тех пор, пока временный указатель не станет равен nullptr
                data[index] = tmp->data; // присвоение текущему элементу массива значения элемента списка
                tmp = tmp->next; // переход к следующему элементу списка
                index++; // увеличение значения счетчика
            }
        }

        div *= 10; // увеличение значения делителя
    }

    std::cout << "\nОтсортированный массив:" << std::endl;
    printArray(data, size);
    std::cout << "\nКоличество перестановок: " << swaps << std::endl;
    delete[] sortedArray; // освобождение памяти
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

// Основное меню
void callMenu() {
    bool work{true};
    int size;
    int *mainArray;
    int compares = 0, swaps = 0;
    while (work) {
        std::cout << "__________________________________________________________________________";
        std::cout << "\nВведите номер команды: \n";
        std::cout << "1. Простейшая карманная сортировка с использованием второго массива\n";
        std::cout << "2. Простейшая карманная сортировка без использованием второго массива\n";
        std::cout << "3. Обобщённая карманная сортировка\n";
        std::cout << "4. Поразрядная сортировка\n";
        std::cout << "5. Завершение работы\n";
        std::cout << "__________________________________________________________________________\n";
        std::cout << "Введите номер команды: ";
        int choice = failure(1, 5);
        switch (choice) {
            case 1:
                std::cout << "Введите размер массива (до " << kMaxSize << "): ";
                size = failure(1, kMaxSize);
                mainArray = new int[size];
                createUniqueArray(mainArray, size);
                std::cout << "\nНеотсортированный массив: \n";
                printArray(mainArray, size);
                simpleBucketSort(mainArray, size, compares);
                break;
            case 2:
                std::cout << "Введите размер массива (до " << kMaxSize << "): ";
                size = failure(1, kMaxSize);
                mainArray = new int[size];
                createUniqueArray(mainArray, size);
                std::cout << "\nНеотсортированный массив: \n";
                printArray(mainArray, size);
                simpleBucketSortNoBucket(mainArray, size, compares, swaps);
                break;
            case 3:
                std::cout << "Введите размер массива (до " << kMaxSize << "): ";
                size = failure(1, kMaxSize);
                mainArray = new int[size];
                for (int i = 0; i < size; i++) {
                    mainArray[i] = rand() % size;
                }
                std::cout << "\nНеотсортированный массив: \n";
                printArray(mainArray, size);
                bucketSort(mainArray, size, swaps);
                break;
            case 4:
                std::cout << "Введите размер массива (до " << kMaxSize << "): ";
                size = failure(1, kMaxSize);
                mainArray = new int[size];
                for (int i = 0; i < size; i++) {
                    mainArray[i] = rand() % size;
                }
                std::cout << "\nНеотсортированный массив: \n";
                printArray(mainArray, size);
                radixSort(mainArray, size, swaps);
                break;
            case 5:
                work = false;
                std::cout << "\nРабота программы завершена.\n";
                break;
            default:
                break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    callMenu();
}