// Раздел 2, тема 3 - СПЕЦИАЛЬНЫЕ МЕТОДЫ СОРТИРОВКИ

#include <iostream>
#include <random>

const int kMaxSize = 10000;

struct ListItem {
    int data;
    ListItem *next;
};

// Функция создания массива с уникальными ключами
void createUniqueArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
    shuffle(arr, arr + size, std::mt19937(std::random_device()()));
}

// Функция вывода массива
void printArray(const int *data, int size) {
    for (int i = 0; i < size; i++) { // цикл по всем элементам массива
        std::cout << data[i] << " "; // вывод очередного элемента на экран
    }
    std::cout << "\n";
}

// Функция выполнения простейшей карманной сортировки с использованием второго массива
void simpleBucketSort(int *data, int size, int &swaps) {
    swaps = 0;
    int maxVal = *std::max_element(data, data + size); // максимальное значение в массиве
    int *bucket = new int[maxVal + 1](); // создаем массив карманов и заполняем его нулями
    for (int i = 0; i < size; i++) {
        bucket[data[i]]++; // увеличиваем значение соответствующего кармана
        swaps++;
    }
    int index = 0;
    for (int i = 0; i <= maxVal; i++) { // цикл по всем карманам
        for (int j = 0; j < bucket[i]; j++) { // цикл по всем элементам в кармане
            data[index] = i; // записываем значение кармана в исходный массив
            index++;
            swaps++;
        }
    }
    std::cout << std::endl << "Отсортированный массив:\n";
    printArray(data, size);
    std::cout << "\nКоличество перестановок: " << swaps << std::endl;
    delete[] bucket;
}

// Функция выполнения простейшей карманной сортировки без использования второго массива
void simpleBucketSortNoBucket(int *data, int size, int &compares, int &swaps) {
    compares = 0;
    swaps = 0;
    int temp;
    for (int i = 0; i < size; i++) {
        temp = data[i];
        while (temp != i) {
            swaps++;
            compares++;
            data[i] = data[temp];
            data[temp] = temp;
            temp = data[i];
        }
        compares++;
    }
    std::cout << std::endl << "Отсортированный массив:\n";
    printArray(data, size);
    std::cout << "\nКоличество перестановок: " << swaps << std::endl;
    std::cout << "Количество сравнений: " << compares << std::endl;
}

// Функция добавления элемента в связный список
void addItem(ListItem *pItem, int value) {
    auto *pNew = new ListItem;
    pNew->data = value;
    pNew->next = nullptr;
    while (pItem->next != nullptr) {
        pItem = pItem->next;
    }
    pItem->next = pNew;
}

// Функция очищения списка
void clearList(ListItem *head) {
    while (head != nullptr) {
        ListItem *temp = head;
        head = head->next;
        delete temp;
    }
}

// Функция отсортированного массива при помощи обобщенной карманной сортировки
void showBucket(ListItem *data, int n) {
    std::cout << "\nОтсортированный массив:" << std::endl;
    for (int i = 0; i < n; i++) {
        ListItem *current = data[i].next;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
    }
    std::cout << std::endl;
}

// Функция выполнения обобщенной карманной сортировки
void bucketSort(int *data, int size, int &swaps) {
    swaps = 0;
    auto *sortedArray = new ListItem[size];
    for (int i = 0; i < size; i++) {
        sortedArray[i].next = nullptr;
    }
    for (int i = 0; i < size; i++, swaps++) {
        addItem(&sortedArray[data[i]], data[i]);
    }
    showBucket(sortedArray, size);
    std::cout << "\nКоличество перестановок: " << swaps << std::endl;
    for (int i = 0; i < size; i++)
        clearList(sortedArray[i].next);
    delete[] sortedArray;
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
        std::cout << "4. Завершение работы\n";
        std::cout << "__________________________________________________________________________\n";
        std::cout << "Введите номер команды: ";
        int choice = failure(1, 4);
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