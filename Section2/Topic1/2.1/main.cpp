// Раздел 2, тема 1 - ПРОСТЕЙШИЕ МЕТОДЫ СОРТИРОВКИ

#include <iostream>
#include <memory>

const int kMaxSize = 10000;

// Функция вывода массива
void printArray(const int *data, int size) {
    for (int i = 0; i < size; i++) { // цикл по всем элементам массива
        std::cout << data[i] << " "; // вывод очередного элемента на экран
    }
    std::cout << "\n";
}

// Функция создания массива
std::unique_ptr<int[]> createArray(int size) {
    // Создание умного указателя на массив из size элементов типа int
    auto data = std::make_unique<int[]>(size);
    std::generate(data.get(), data.get() + size, std::rand); // заполнение массива случайными числами
    std::cout << "\nНеотсортированный массив:" << std::endl;
    printArray(data.get(), size);
    return data;
}

// Функция выполнения сортировки пузырьком
void bubbleSort(int *data, int size, int &compares, int &swaps) {
    compares = swaps = 0;
    for (int i = 1; i < size; i++) { // цикл по всем элементам массива, кроме первого
        for (int j = size - 1; j >= i; j--) { // цикл по неотсортированной части массива
            if (data[j - 1] > data[j]) { // если предыдущий элемент больше текущего
                std::swap(data[j - 1], data[j]); // меняем элементы местами
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
    for (int i = 0; i < size - 1; i++) { // проходим по всем элементам массива, кроме последнего
        int minIdx = i; // индекс минимального элемента устанавливаем на i
        for (int j = i + 1; j < size; j++) { // проходим по всем элементам, начиная со следующего после i
            compares++;
            if (data[j] < data[minIdx]) { // если текущий элемент меньше минимального
                minIdx = j; // обновляем индекс минимального элемента
            }
        }
        std::swap(data[minIdx], data[i]); // меняем местами минимальный элемент и текущий элемент
        swaps++;
    }
    printArray(data, size);
}

// Функция выполнения сортировки вставками
void insertionSort(int *data, int size, int &compares, int &swaps) {
    compares = swaps = 0;
    for (int i = 1; i < size; i++) { // проходим по всем элементам массива, начиная со второго
        int j = i - 1; // устанавливаем j на предыдущий элемент
        int key = data[i]; // запоминаем текущий элемент
        while (j >= 0 && data[j] > key) { // пока j >= 0 и предыдущий элемент больше текущего
            compares++;
            data[j + 1] = data[j]; // сдвигаем предыдущий элемент на одну позицию вправо
            swaps++;
            j--;
        }
        compares++;
        data[j + 1] = key; // вставляем текущий элемент на освободившееся место
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
    std::cout << "Введите размер массива (до " << kMaxSize << "): ";
    size = failure(1, kMaxSize);
    auto data = createArray(size);
    auto arrCopy = std::make_unique<int[]>(size);  // создаем копию массива
    bool work = true;
    while (work) {
        std::cout << "____________________________________________";
        std::cout << "\nВарианты команд:\n";
        std::cout << "1. Сортировка обменом (метод пузырька)\n";
        std::cout << "2. Сортировка выбором\n";
        std::cout << "3. Сортировка вставками\n";
        std::cout << "4. Завершение работы\n";
        std::cout << "____________________________________________\n";
        std::cout << "Введите номер команды: ";
        int choice = failure(1, 4);
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
