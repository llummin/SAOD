// Лабораторная работа №8 (раздел 1, тема 4, номер 3) - СПИСОК СПИСКОВ НА ОСНОВЕ ЛИНЕЙНОГО ДИНАМИЧЕСКОГО СПИСКА

#include <iostream>
#include <string>
#include <set>
#include <utility>

struct SubListItem {
    SubListItem *next;
    int data;
};

struct MainListItem {
    MainListItem *pMainList{};
    SubListItem *pSubList{};
    std::string dataStr;
};

MainListItem *head;

// Ввод целочисленного значения с проверкой
int failure() {
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

// Ввод строки с проверкой на пустоту
std::string checkStringNotEmpty() {
    std::string str;
    bool is_space;
    while (true) {
        getline(std::cin, str);
        if (str.empty()) {
            std::cout << "Вы ввели пустую строку. Попробуйте еще раз: ";
        } else {
            is_space = true;
            for (char i: str) {
                if (!isspace(i)) {
                    is_space = false;
                    break;
                }
            }
            if (is_space) {
                std::cout << "Вы ввели пустую строку. Попробуйте еще раз: ";
            } else {
                return str;
            }
        }
    }
}

// Функция инициализации списка списков
void initList(MainListItem *&headItem) {
    headItem->pMainList = nullptr;
    headItem->pSubList = nullptr;
    headItem->dataStr = " ";
}

// Функция проверки главного списка на пустоту
bool isEmpty(MainListItem *headItem) {
    return headItem->pMainList == nullptr;
}

// Функция проверки вспомогательного списка на пустоту
bool isEmpty(SubListItem *headItem) {
    return headItem->next == nullptr;
}

// Функция для отображения текущего состояния списка
void printList() {
    MainListItem *currMain = head->pMainList;
    while (currMain != nullptr) {
        std::cout << currMain->dataStr << ": ";
        SubListItem *currSub = currMain->pSubList;
        if (isEmpty(currSub)) {
            std::cout << "пусто\n";
        } else {
            while (currSub != nullptr) {
                std::cout << currSub->data << " ";
                currSub = currSub->next;
            }
            std::cout << std::endl;
        }
        currMain = currMain->pMainList;
    }
}

// Поиск в главном списке
MainListItem *mainSearch(const std::string &strToSearch) {
    MainListItem *cur = head->pMainList;
    while (cur != nullptr) {
        if (cur->dataStr == strToSearch) {
            return cur;
        }
        cur = cur->pMainList;
    }
    return nullptr;
}

// Функция добавления нового элемента перед заданным в главный список
void mainInsertBefore(std::string strToAdd, const std::string &strToBefore) {
    MainListItem *current = head->pMainList;
    MainListItem *previous = head;
    while (current->dataStr != strToBefore) {
        previous = current;
        current = current->pMainList;
    }
    auto *newItem = new MainListItem;
    auto *newSub = new SubListItem;
    newSub->data = 0;
    newSub->next = nullptr;
    newItem->dataStr = std::move(strToAdd);
    newItem->pMainList = current;
    newItem->pSubList = newSub;
    previous->pMainList = newItem;
    std::cout << "\nДобавлен элемент " << newItem->dataStr << "\n";
}

// Функция добавления нового элемента после заданного в главный список
void mainInsertAfter(std::string strToAdd, MainListItem *pTemp) {
    auto *newItem = new MainListItem;
    auto *newSub = new SubListItem;
    newSub->data = 0;
    newSub->next = nullptr;
    newItem->dataStr = std::move(strToAdd);
    newItem->pMainList = pTemp->pMainList;
    newItem->pSubList = newSub;
    pTemp->pMainList = newItem;
    std::cout << "\nДобавлен элемент " << newItem->dataStr << "\n";
}

void callMenu(MainListItem *&headItem) {
    bool work{true};
    while (work) {
        std::cout << "___________________________________________________________";
        std::cout << "\nВведите номер команды: \n";
        std::cout << "1. Вывести текущее состояние списка списков\n";
        std::cout << "2. Добавление элемента в главный список перед заданным\n";
        std::cout << "3. Добавление элемента в главный список после заданного\n";
        std::cout << "4. Завершение работы\n";
        std::cout << "___________________________________________________________\n";
        std::cout << "Введите номер команды: ";
        MainListItem *pTemp;
        std::string strToBefore;
        int choice = failure(1, 4);
        switch (choice) {
            case 1:
                if (isEmpty(headItem)) {
                    std::cout << "\nСписок пуст!\n";
                } else {
                    std::cout << "\nСписки:\n";
                    printList();
                }
                break;
            case 2:
                if (isEmpty(headItem)) {
                    std::cout << "\nВведите название списка, который хотели бы добавить: ";
                    mainInsertAfter(checkStringNotEmpty(), headItem);
                    break;
                }
                std::cout << "\nВведите элемент, перед которым хотите добавить новый: ";
                strToBefore = checkStringNotEmpty();
                pTemp = mainSearch(strToBefore);
                if (pTemp == nullptr) {
                    std::cout << "\nТакого элемента в главном списке не существует.\n";
                    break;
                }
                std::cout << "\nВведите имя списка, который хотели бы добавить в главный: ";
                mainInsertBefore(checkStringNotEmpty(), strToBefore);
                break;
            case 3:
                if (isEmpty(headItem)) {
                    std::cout << "\nВведите название списка, который хотели бы добавить: ";
                    mainInsertAfter(checkStringNotEmpty(), headItem);
                    break;
                }
                std::cout << "\nВведите элемент, перед которым хотите добавить новый: ";
                pTemp = mainSearch(checkStringNotEmpty());
                if (pTemp == nullptr) {
                    std::cout << "\nТакого элемента в главном списке не существует.\n";
                    break;
                }
                std::cout << "\nВведите имя списка, который хотели бы добавить в главный: ";
                mainInsertAfter(checkStringNotEmpty(), pTemp);
                break;
            case 4:
                work = false;
                std::cout << "\nПрограмма завершена\n";
                break;
            default:
                break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    head = new MainListItem;
    initList(head);
    callMenu(head);
}