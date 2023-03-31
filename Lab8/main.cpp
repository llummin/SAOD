// Лабораторная работа №8 (раздел 1, тема 4, номер 3) - СПИСОК СПИСКОВ НА ОСНОВЕ ЛИНЕЙНОГО ДИНАМИЧЕСКОГО СПИСКА

#include <iostream>

struct SubListItem {
    int data;
    SubListItem *next;
};

struct MainListItem {
    std::string dataStr;
    MainListItem *pMainList{};
    SubListItem *pSubList{};
};

MainListItem *head;

// Функция инициализации списка списков
void initList(MainListItem *&headItem) {
    headItem->pMainList = nullptr;
    headItem->pSubList = nullptr;
    headItem->dataStr = " ";
}

// Функция проверки главного списка на пустоту
bool mainIsEmpty(MainListItem *headItem) {
    return headItem->pMainList == nullptr;
}

// Функция проверки вспомогательного списка на пустоту
bool subIsEmpty(SubListItem *headItem) {
    return headItem->next == nullptr;
}

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

// Поиск во вспомогательном списке
SubListItem *subSearch(int intToSearch) {
    MainListItem *pMainCur = head->pMainList;
    while (pMainCur != nullptr) {
        SubListItem *pSubCur = (pMainCur->pSubList)->next;
        while (pSubCur != nullptr) {
            if (pSubCur->data == intToSearch) {
                return pSubCur;
            }
            pSubCur = pSubCur->next;
        }
        pMainCur = pMainCur->pMainList;
    }
    return nullptr;
}

// Поиск в списке
SubListItem *searchInList(int intToSearch, SubListItem *subHead) {
    SubListItem *pCur = subHead;
    while (pCur != nullptr) {
        if (pCur->data == intToSearch) {
            return pCur;
        }
        pCur = pCur->next;
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
    std::cout << "\nДобавлен элемент " << newItem->dataStr << " в главный список\n";
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
    std::cout << "\nДобавлен элемент " << newItem->dataStr << " в главный список\n";
}

// Функция добавления нового элемента во вспомогательный список перед заданным
void subInsertBefore(int intToAdd, SubListItem *pHead, int intToBefore) {
    auto *newSub = new SubListItem;
    SubListItem *current = pHead->next;
    SubListItem *previous = pHead;
    while (current->data != intToBefore) {
        previous = current;
        current = current->next;
    }
    newSub->data = intToAdd;
    newSub->next = current;
    previous->next = newSub;
    std::cout << "\nДобавлен элемент " << newSub->data << " во вспомогательный список\n";
}

// Функция добавления нового элемента во вспомогательный список после заданного
void subInsertAfter(int intToAdd, SubListItem *pTemp) {
    auto *newSub = new SubListItem;
    newSub->data = intToAdd;
    newSub->next = pTemp->next;
    pTemp->next = newSub;
    std::cout << "\nДобавлен элемент " << newSub->data << " во вспомогательный список\n";
}

// Функция удаления элемента в главном списке
void mainRemove(const std::string &strToDel) {
    MainListItem *pTemp = head->pMainList;
    MainListItem *pPrev = head;
    while (pTemp != nullptr) {
        if (pTemp->dataStr == strToDel) {
            SubListItem *pSub = pTemp->pSubList;
            while (pSub != nullptr) {
                SubListItem *pSubTemp = pSub;
                pSub = pSub->next;
                delete pSubTemp;
            }
            pPrev->pMainList = pTemp->pMainList;
            delete pTemp;
            std::cout << "\nУдален элемент " << strToDel << " из главного списка\n";
            break;
        }
        pPrev = pTemp;
        pTemp = pTemp->pMainList;
    }
}

// Функция удаления элемента во вспомогательном списке
void subRemove(int intToDel, SubListItem *subHead) {
    SubListItem *pTemp = subHead->next;
    SubListItem *pPrev = subHead;
    while (pTemp != nullptr) {
        if (pTemp->data == intToDel) {
            pPrev->next = pTemp->next;
            delete pTemp;
            std::cout << "\nУдален элемент " << intToDel << " из вспомогательного списка\n";
            break;
        }
        pPrev = pTemp;
        pTemp = pTemp->next;
    }
}

// Функция для отображения текущего состояния списка
void printList() {
    MainListItem *currMain = head->pMainList;
    while (currMain != nullptr) {
        std::cout << currMain->dataStr << ": ";
        SubListItem *currSub = currMain->pSubList;
        if (subIsEmpty(currSub)) {
            std::cout << "пусто\n";
        } else {
            // Проверка, является ли первый элемент вспомогательного списка равным нулю
            if (currSub->data == 0) {
                currSub = currSub->next;
            }
            while (currSub != nullptr) {
                std::cout << currSub->data << " ";
                currSub = currSub->next;
            }
            std::cout << std::endl;
        }
        currMain = currMain->pMainList;
    }
}

// Основное меню
void callMenu(MainListItem *&headItem) {
    bool work{true};
    int choice;
    while (work) {
        std::cout << "_______________________________________________________________________";
        std::cout << "\nВведите номер команды: \n";
        std::cout << "1. Вывести текущее состояние списка списков\n";
        std::cout << "2. Добавление элемента в главный список перед заданным\n";
        std::cout << "3. Добавление элемента в главный список после заданного\n";
        std::cout << "4. Добавление элемента во вспомогательный список перед заданным\n";
        std::cout << "5. Добавление элемента во вспомогательный список после заданного\n";
        std::cout << "6. Удаление элемента в главном списке\n";
        std::cout << "7. Удаление элемента во вспомогательном списке\n";
        std::cout << "8. Поиск элемента в главном списке\n";
        std::cout << "9. Поиск элемента во вспомогательном списке \n";
        std::cout << "10. Завершение работы\n";
        std::cout << "_______________________________________________________________________\n";
        std::cout << "Введите номер команды: ";
        choice = failure(1, 10);
        MainListItem *pMain;
        SubListItem *pSub;
        std::string strToDel, strToBefore;
        int intToDel, intToBefore;
        switch (choice) {
            case 1:
                if (mainIsEmpty(headItem)) {
                    std::cout << "\nСписок списков пуст!\n";
                } else {
                    std::cout << "\nСписки:\n";
                    printList();
                }
                break;
            case 2:
                if (mainIsEmpty(headItem)) {
                    std::cout << "\nВведите название списка, который хотели бы добавить: ";
                    mainInsertAfter(checkStringNotEmpty(), headItem);
                    break;
                }
                std::cout << "\nВведите элемент, перед которым хотите добавить новый: ";
                strToBefore = checkStringNotEmpty();
                pMain = mainSearch(strToBefore);
                if (pMain == nullptr) {
                    std::cout << "\nТакого элемента в главном списке не существует.\n";
                    break;
                }
                std::cout << "\nВведите название списка, который хотели бы добавить: ";
                mainInsertBefore(checkStringNotEmpty(), strToBefore);
                break;
            case 3:
                if (mainIsEmpty(headItem)) {
                    std::cout << "\nВведите название списка, который хотели бы добавить: ";
                    mainInsertAfter(checkStringNotEmpty(), headItem);
                    break;
                }
                std::cout << "\nВведите элемент, перед которым хотите добавить новый: ";
                pMain = mainSearch(checkStringNotEmpty());
                if (pMain == nullptr) {
                    std::cout << "\nТакого элемента в главном списке не существует.\n";
                    break;
                }
                std::cout << "\nВведите название списка, который хотели бы добавить: ";
                mainInsertAfter(checkStringNotEmpty(), pMain);
                break;
            case 4:
                if (mainIsEmpty(headItem)) {
                    std::cout << "\nГлавный список пуст! Добавление во вспомогательный невозможно!\n";
                    break;
                }
                std::cout << "\nВведите название списка, в который хотели бы добавить новый элемент: ";
                pMain = mainSearch(checkStringNotEmpty());
                if (pMain == nullptr) {
                    std::cout << "\nТакого названия главного списка не существует.\n";
                    break;
                }
                if (subIsEmpty(pMain->pSubList)) {
                    std::cout << "\nВведите число, которое хотели бы добавить во вспомогательный список: ";
                    subInsertAfter(failure(), pMain->pSubList);
                    break;
                }

                std::cout << "\nВведите элемент, перед которым хотите добавить новый: ";
                intToBefore = failure();
                pSub = searchInList(intToBefore, pMain->pSubList);
                if (pSub == nullptr) {
                    std::cout << "\nТакого названия главного списка не существует.\n";
                    break;
                }
                std::cout << "\nВведите число, которое хотели бы добавить во вспомогательный список: ";
                subInsertBefore(failure(), pMain->pSubList, intToBefore);
                break;
            case 5:
                if (mainIsEmpty(headItem)) {
                    std::cout << "\nГлавный список пуст! Добавление во вспомогательный невозможно!\n";
                    break;
                }
                std::cout << "\nВведите название списка, в который хотели бы добавить новый элемент: ";
                pMain = mainSearch(checkStringNotEmpty());
                if (pMain == nullptr) {
                    std::cout << "\nТакого названия главного списка не существует.\n";
                    break;
                }
                if (subIsEmpty(pMain->pSubList)) {
                    std::cout << "\nВведите число, которое хотели бы добавить во вспомогательный список: ";
                    subInsertAfter(failure(), pMain->pSubList);
                    break;
                }

                std::cout << "\nВведите элемент, после которого хотите добавить новый: ";
                pSub = searchInList(failure(), pMain->pSubList);
                if (pSub == nullptr) {
                    std::cout << "\nТакого названия главного списка не существует.\n";
                    break;
                }
                std::cout << "\nВведите число, которое хотели бы добавить во вспомогательный список: ";
                subInsertAfter(failure(), pSub);
                break;
            case 6:
                if (mainIsEmpty(headItem)) {
                    std::cout << "\nГлавный список пуст! Удаление невозможно!\n";
                    break;
                }
                std::cout << "\nВведите название списка, который хотели бы удалить: ";
                strToDel = checkStringNotEmpty();
                if ((mainSearch(strToDel)) == nullptr) {
                    std::cout << "\nТакого названия главного списка не существует.\n";
                    break;
                }
                mainRemove(strToDel);
                break;
            case 7:
                if (mainIsEmpty(headItem)) {
                    std::cout << "\nГлавный список пуст! Удаление во вспомогательном списке невозможно!\n";
                    break;
                }
                std::cout << "\nВведите название главного списка, в котором хотели бы удалить элемент: ";
                strToDel = checkStringNotEmpty();
                pMain = mainSearch(strToDel);
                if (pMain == nullptr) {
                    std::cout << "\nТакого названия главного списка не существует.\n";
                    break;
                }
                if (subIsEmpty(pMain->pSubList)) {
                    std::cout << "\nВспомогательный список пуст! Удаление невозможно!\n";
                    break;
                }
                std::cout << "\nВведите элемент, который хотели бы удалить во вспомогательном списке: ";
                intToDel = failure();
                if ((subSearch(intToDel)) == nullptr) {
                    std::cout << "\nДанный элемент не найден.\n";
                    break;
                }
                subRemove(intToDel, pMain->pSubList);
                break;
            case 8: {
                if (mainIsEmpty(head)) {
                    std::cout << "\nГлавный список пуст! Поиск невозможен!\n";
                    break;
                }
                std::cout << "\nВведите название главного списка: ";
                MainListItem *foundMain = mainSearch(checkStringNotEmpty());
                if (foundMain == nullptr) {
                    std::cout << "\nДанный список не найден.\n";
                    break;
                }
                int index = 0;
                MainListItem *cur = head->pMainList;
                while (cur != foundMain) {
                    index++;
                    cur = cur->pMainList;
                }
                std::cout << "\nДанный список найден. Индекс элемента в главном списке: " << index << std::endl;
                break;
            }
            case 9: {
                if (mainIsEmpty(head)) {
                    std::cout << "\nГлавный список пуст! Поиск невозможен!\n";
                    break;
                }
                std::cout << "\nВведите название главного списка: ";
                MainListItem *foundMain = mainSearch(checkStringNotEmpty());
                if (foundMain == nullptr) {
                    std::cout << "\nДанный список не найден.\n";
                    break;
                }
                if (subIsEmpty(foundMain->pSubList)) {
                    std::cout << "\nВспомогательный список пуст! Поиск невозможен!\n";
                    break;
                }
                std::cout << "\nВведите целочисленное значение для поиска: ";
                int intToSearch = failure();
                SubListItem *foundSub = subSearch(intToSearch);
                if (foundSub == nullptr) {
                    std::cout << "\nДанный элемент не найден.\n";
                    break;
                }
                int subIndex = 0;
                SubListItem *subCur = foundMain->pSubList->next;
                while (subCur != foundSub) {
                    subIndex++;
                    subCur = subCur->next;
                }
                std::cout << "\nДанный элемент найден. Индекс элемента во вспомогательном списке: " << subIndex
                          << std::endl;
                break;
            }
            case 10:
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