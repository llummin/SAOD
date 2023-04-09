// Раздел 2, тема 1 - ПРОСТЕЙШИЕ МЕТОДЫ СОРТИРОВКИ

#include <iostream>
#include <memory>

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

// Функция выполнения сортировки пузырьком заданного массива
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
        std::cout << "2. Завершение работы\n";
        std::cout << "____________________________________________\n";
        std::cout << "Введите номер команды: ";
        int choice = failure(1, 2);
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
