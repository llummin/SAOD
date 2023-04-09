// Раздел 2, тема 2 - ПРОСТЕЙШИЕ МЕТОДЫ СОРТИРОВКИ + УЛУЧШЕННЫЕ МЕТОДЫ СОРТИРОВКИ

#include <iostream>
#include <memory>
#include <cmath>

const int kMaxVolume = 10000;

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

// Функция выполнения сортировки методом Шелла
void shellSort(int *data, int size, int &compares, int &swaps) {
    compares = swaps = 0;
    int t = (int) log2(size) - 1; // определяем количество промежутков (шагов)
    int *h = new int[t]; // выделяем память под массив шагов
    for (int m = 1; m <= t; m++) { // вычисляем значения шагов
        h[m - 1] = static_cast<int>(pow(2, t - m + 1)) - 1;
    }

    for (int m = 0; m < t; m++) { // проходим по всем шагам
        int k = h[m]; // получаем текущий шаг
        for (int i = k; i < size; i++) { // проходим по массиву, начинающемуся с k-го элемента
            int temp = data[i]; // запоминаем текущий элемент
            int j = i - k;
            while (j >= 0 && temp < data[j]) { // ищем позицию для вставки текущего элемента
                compares++;
                data[j + k] = data[j]; // сдвигаем элементы вправо
                j = j - k;
                swaps++;
            }
            compares++;
            data[j + k] = temp; // вставляем текущий элемент в найденную позицию
        }
    }

    delete[] h; // освобождаем память, выделенную под массив шагов
    printArray(data, size);
}

// Функция выполнения сортировки методом быстрой сортировки
void quickSort(int *data, int begin, int end, int &compares, int &swaps) {
    // Установка границ и опорного элемента
    int i = begin, j = end;
    int pivot = data[(begin + end) / 2];

    // Основной цикл сортировки
    while (i <= j) {
        while (data[i] < pivot) { // поиск элемента, больше или равного опорному с левой границы
            i++;
            compares++;
        }
        while (data[j] > pivot) { // поиск элемента, меньше или равного опорному с правой границы
            j--;
            compares++;
        }
        if (i <= j) { // обмен элементов и сдвиг границ
            std::swap(data[i], data[j]);
            i++;
            j--;
            swaps++;
        }
    }

    // Рекурсивный вызов функции для левой и правой частей массива
    if (begin < j) {
        quickSort(data, begin, j, compares, swaps);
    }
    if (i < end) {
        quickSort(data, i, end, compares, swaps);
    }
}

// Вспомогательная функция по просеиванию элементов
void heapify(int *data, int left, int right, int &compares, int &swaps) {
    // Инициализация индексов i и j, а также переменной x значением первого элемента в массиве
    int i = left, j = 2 * left, x = data[left];
    // Проверка наличия правого потомка и сравнение значений левого и правого потомков
    if (j < right && data[j + 1] > data[j]) {
        j++; // если правый потомок существует и больше левого, выбираем его
    }
    compares++;
    // Перебираем элементы массива до тех пор, пока значение x меньше текущего элемента
    while (j <= right && data[j] > x) {
        compares++;
        data[i] = data[j]; // перемещаем текущий элемент на место родителя
        i = j; // обновляем индексы
        j = 2 * j;
        swaps++;
        if (j < right && data[j + 1] > data[j]) { // проверяем, какой из потомков больше, и выбираем его
            j++;
        }
        compares++;
    }
    compares++;
    data[i] = x; // помещаем значение x на свое место в массиве
    swaps++;
}

// Функция выполнения пирамидальной сортировки
void heapSort(int *data, int size, int &compares, int &swaps) {
    compares = swaps = 0;
    int left = (size / 2) + 2; // определяем начальное значение индекса левого потомка последнего узла
    int right = size - 1;

    while (left > 0) { // создаем начальную пирамиду
        left--;
        heapify(data, left, right, compares, swaps);
    }

    // проходим по элементам от конца массива к началу,
    // меняем первый элемент с последним и вызываем heapify для корректировки пирамиды
    while (right > 0) {
        std::swap(data[0], data[right]);
        swaps++;
        right--;
        heapify(data, left, right, compares, swaps);
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
        std::cout << "2. Сортировка выбором\n";
        std::cout << "3. Сортировка вставками\n";
        std::cout << "4. Сортировка методом Шелла\n";
        std::cout << "5. Сортировка методом быстрой сортировки\n";
        std::cout << "6. Пирамидальная сортировка\n";
        std::cout << "7. Завершение работы\n";
        std::cout << "____________________________________________\n";
        std::cout << "Введите номер команды: ";
        int choice = failure(1, 7);
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
                std::cout << "\nНеотсортированный массив: \n";
                printArray(data.get(), size);
                std::cout << "\nОтсортированный массив: \n";
                heapSort(arrCopy.get(), size, compares, swaps);
                std::cout << "\nЧисло сравнений: " << compares << std::endl;
                std::cout << "Число перестановок: " << swaps << std::endl;
                break;
            case 7:
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
