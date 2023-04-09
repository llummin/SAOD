// Раздел 2, тема 2 - ПРОСТЕЙШИЕ МЕТОДЫ СОРТИРОВКИ + УЛУЧШЕННЫЕ МЕТОДЫ СОРТИРОВКИ

#include <iostream>
#include <memory>
#include <cmath>

const int kMaxVolume = 10000;

// Функция вывода массива
void printArray(const int *data, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << "\n";
}

// Функция создания массива
std::unique_ptr<int[]> createArray(int size) {
    auto data = std::make_unique<int[]>(size);
    std::generate(data.get(), data.get() + size, std::rand);
    std::cout << "\nНеотсортированный массив:" << std::endl;
    printArray(data.get(), size);
    return data;
}

// Функция выполнения сортировки пузырьком
void bubbleSort(int *data, int size, int &compares, int &swaps) {
    compares = swaps = 0;
    for (int i = 1; i < size; i++) {
        for (int j = size - 1; j >= i; j--) {
            if (data[j - 1] > data[j]) {
                std::swap(data[j - 1], data[j]);
                swaps++;
            }
            compares++;
        }
    }
    printArray(data, size);
}

// Функция выполнения сортировки выбором
void selectionSort(int *data, int size, int &compares, int &swaps) {
    compares = swaps = 0;
    for (int i = 0; i < size - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < size; j++) {
            compares++;
            if (data[j] < data[minIdx]) {
                minIdx = j;
            }
        }
        std::swap(data[minIdx], data[i]);
        swaps++;
    }
    printArray(data, size);
}

// Функция выполнения сортировки вставками
void insertionSort(int *data, int size, int &compares, int &swaps) {
    compares = swaps = 0;
    for (int i = 1; i < size; i++) {
        int j = i - 1;
        int key = data[i];
        while (j >= 0 && data[j] > key) {
            compares++;
            data[j + 1] = data[j];
            swaps++;
            j--;
        }
        compares++;
        data[j + 1] = key;
    }
    printArray(data, size);
}

// Функция выполнения сортировки методом Шелла
void shellSort(int *data, int size, int &compares, int &swaps) {
    compares = swaps = 0;
    int t = (int) log2(size) - 1;
    int *h = new int[t];
    for (int m = 1; m <= t; m++) {
        h[m - 1] = static_cast<int>(pow(2, t - m + 1)) - 1;
    }

    for (int m = 0; m < t; m++) {
        int k = h[m];
        for (int i = k; i < size; i++) {
            int temp = data[i];
            int j = i - k;
            while (j >= 0 && temp < data[j]) {
                compares++;
                data[j + k] = data[j];
                j = j - k;
                swaps++;
            }
            compares++;
            data[j + k] = temp;
        }
    }

    delete[] h;
    printArray(data, size);
}

// Функция выполнения сортировки методом быстрой сортировки
void quickSort(int *data, int begin, int end, int &compares, int &swaps) {
    int i = begin, j = end;
    int pivot = data[(begin + end) / 2];

    while (i <= j) {
        while (data[i] < pivot) {
            i++;
            compares++;
        }
        while (data[j] > pivot) {
            j--;
            compares++;
        }
        if (i <= j) {
            std::swap(data[i], data[j]);
            i++;
            j--;
            swaps++;
        }
    }

    if (begin < j) {
        quickSort(data, begin, j, compares, swaps);
    }
    if (i < end) {
        quickSort(data, i, end, compares, swaps);
    }
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
    int size;
    std::cout << "Введите размер массива (до " << kMaxVolume << "): ";
    size = failure(1, kMaxVolume);
    auto data = createArray(size);
    auto arrCopy = std::make_unique<int[]>(size);  // создаем копию массива
    bool work = true;
    while (work) {
        std::cout << "____________________________________________";
        std::cout << "\nВарианты команд:\n";
        std::cout << "1. Сортировка обменом (метод пузырька)\n";
        std::cout << "2. Сортировка выбором\n";
        std::cout << "3. Сортировка вставками\n";
        std::cout << "4. Сортировка методом Шелла\n";
        std::cout << "5. Сортировка методом быстрой сортировки\n";
        std::cout << "6. Завершение работы\n";
        std::cout << "____________________________________________\n";
        std::cout << "Введите номер команды: ";
        int choice = failure(1, 6);
        std::copy(data.get(), data.get() + size, arrCopy.get());  // копируем неотсортированный массив
        int compares = 0, swaps = 0;
        switch (choice) {
            case 1:
                std::cout << "\nНеотсортированный массив: \n";
                printArray(data.get(), size);
                std::cout << "\nОтсортированный массив: \n";
                bubbleSort(arrCopy.get(), size, compares, swaps);
                std::cout << "\nЧисло сравнений: " << compares << std::endl;
                std::cout << "Число перестановок: " << swaps << std::endl;
                break;
            case 2:
                std::cout << "\nНеотсортированный массив: \n";
                printArray(data.get(), size);
                std::cout << "\nОтсортированный массив: \n";
                selectionSort(arrCopy.get(), size, compares, swaps);
                std::cout << "\nЧисло сравнений: " << compares << std::endl;
                std::cout << "Число перестановок: " << swaps << std::endl;
                break;
            case 3:
                std::cout << "\nНеотсортированный массив: \n";
                printArray(data.get(), size);
                std::cout << "\nОтсортированный массив: \n";
                insertionSort(arrCopy.get(), size, compares, swaps);
                std::cout << "\nЧисло сравнений: " << compares << std::endl;
                std::cout << "Число перестановок: " << swaps << std::endl;
                break;
            case 4:
                std::cout << "\nНеотсортированный массив: \n";
                printArray(data.get(), size);
                std::cout << "\nОтсортированный массив: \n";
                shellSort(arrCopy.get(), size, compares, swaps);
                std::cout << "\nЧисло сравнений: " << compares << std::endl;
                std::cout << "Число перестановок: " << swaps << std::endl;
                break;
            case 5:
                std::cout << "\nНеотсортированный массив: \n";
                printArray(data.get(), size);
                std::cout << "\nОтсортированный массив: \n";
                quickSort(arrCopy.get(), 0, size - 1, compares, swaps);
                printArray(arrCopy.get(), size);
                std::cout << "\nЧисло сравнений: " << compares << std::endl;
                std::cout << "Число перестановок: " << swaps << std::endl;
                break;
            case 6:
                work = false;
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
