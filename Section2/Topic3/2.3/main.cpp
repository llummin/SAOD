// Раздел 2, тема 3 - СПЕЦИАЛЬНЫЕ МЕТОДЫ СОРТИРОВКИ

#include <iostream>
#include <random>

const int kMaxSize = 10000;

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
        std::cout << "2. Завершение работы\n";
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