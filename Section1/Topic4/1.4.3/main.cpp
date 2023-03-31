// Раздел 1, тема 4, номер 3 - СПИСОК СПИСКОВ НА ОСНОВЕ ЛИНЕЙНОГО ДИНАМИЧЕСКОГО СПИСКА

#include <iostream>

// Структура элемента вспомогательного списка
struct SubListItem {
    int data; // данные элемента
    SubListItem *next; // указатель на следующий элемент списка
};

// Структура элемента главного списка
struct MainListItem {
    std::string dataStr; // данные элемента
    MainListItem *pMainList{}; // указатель на следующий элемент главного списка
    SubListItem *pSubList{}; // указатель на голову вспомогательного списка
};

MainListItem *head; // указатель на голову главного списка

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
MainListItem *mainSearch(const std::string &strToSearch) { // принимает ссылку на строку, которую нужно найти
    MainListItem *cur = head->pMainList; // устанавливаем указатель на начало главного списка
    while (cur != nullptr) { // проходим по главному списку, пока не дойдем до конца
        if (cur->dataStr == strToSearch) { // если найден элемент с заданной строкой
            return cur; // возвращаем указатель на найденный элемент
        }
        cur = cur->pMainList; // переходим к следующему элементу
    }
    return nullptr; // если элемент не найден, возвращаем nullptr
}

// Поиск во вспомогательном списке
SubListItem *subSearch(int intToSearch) {
    MainListItem *pMainCur = head->pMainList; // устанавливаем указатель на начало главного списка
    while (pMainCur != nullptr) { // проходим по главному списку, пока не дойдем до конца
        SubListItem *pSubCur = (pMainCur->pSubList)->next; // устанавливаем указатель на начало вспомогательного списка
        while (pSubCur != nullptr) { // проходим по вспомогательному списку, пока не дойдем до конца
            if (pSubCur->data == intToSearch) { // если найден элемент с заданным числом
                return pSubCur; // возвращаем указатель на найденный элемент
            }
            pSubCur = pSubCur->next; // переходим к следующему элементу
        }
        pMainCur = pMainCur->pMainList; // переходим к следующему главному элементу
    }
    return nullptr; // если элемент не найден, возвращаем nullptr
}

// Поиск в списке
SubListItem *searchInList(int intToSearch, SubListItem *subHead) {
    SubListItem *pCur = subHead; // создаем указатель на текущий элемент и устанавливаем его на голову списка
    while (pCur != nullptr) { // пока текущий элемент не станет нулевым
        if (pCur->data == intToSearch) { // если значение текущего элемента равно искомому значению
            return pCur; // возвращаем указатель на текущий элемент
        }
        pCur = pCur->next; // переходим к следующему элементу списка
    }
    return nullptr; // если искомый элемент не найден, возвращаем нулевой указатель
}

// Функция добавления нового элемента перед заданным в главный список
void mainInsertBefore(std::string strToAdd, const std::string &strToBefore) {
    MainListItem *current = head->pMainList; // создаем указатель на текущий элемент и устанавливаем его на первый элемент списка
    MainListItem *previous = head; // создаем указатель на предыдущий элемент и устанавливаем его на голову списка
    while (current->dataStr !=
           strToBefore) { // пока значение текущего элемента не равно значению, перед которым нужно вставить новый элемент
        previous = current; // запоминаем текущий элемент как предыдущий
        current = current->pMainList; // переходим к следующему элементу списка
    }
    auto *newItem = new MainListItem; // выделяем память под новый элемент главного списка
    auto *newSub = new SubListItem; // выделяем память под новый элемент вспомогательного списка
    newSub->data = 0; // устанавливаем значение нового элемента вспомогательного списка в 0
    newSub->next = nullptr; // указываем, что следующий элемент списка не существует
    newItem->dataStr = std::move(strToAdd); // копируем значение нового элемента главного списка
    newItem->pMainList = current; // устанавливаем указатель на следующий элемент главного списка
    newItem->pSubList = newSub; // устанавливаем указатель на голову вспомогательного списка
    previous->pMainList = newItem; // устанавливаем указатель предыдущего элемента на новый элемент главного списка
    std::cout << "\nДобавлен элемент " << newItem->dataStr << " в главный список\n";
}

// Функция добавления нового элемента после заданного в главный список
void mainInsertAfter(std::string strToAdd, MainListItem *pTemp) {
    auto *newItem = new MainListItem; // выделяем память под новый элемент главного списка
    auto *newSub = new SubListItem; // выделяем память под новый элемент вспомогательного списка
    newSub->data = 0; // устанавливаем значение нового элемента вспомогательного списка в 0
    newSub->next = nullptr; // указываем, что следующий элемент списка не существует
    newItem->dataStr = std::move(strToAdd); // копируем значение нового элемента главного списка
    newItem->pMainList = pTemp->pMainList; // устанавливает указатель на следующий элемент главного списка
    newItem->pSubList = newSub; // устанавливает указатель на вспомогательный список нового элемента главного списка
    pTemp->pMainList = newItem; // устанавливает указатель на следующий элемент главного списка
    std::cout << "\nДобавлен элемент " << newItem->dataStr << " в главный список\n";
}

// Функция добавления нового элемента во вспомогательный список перед заданным
void subInsertBefore(int intToAdd, SubListItem *pHead, int intToBefore) {
    auto *newSub = new SubListItem; // создание нового узла вспомогательного списка
    SubListItem *current = pHead->next; // указатель на первый узел вспомогательного списка
    SubListItem *previous = pHead; // указатель на голову вспомогательного списка
    while (current->data != intToBefore) { // поиск узла с данным значением
        previous = current; // обновление указателя на предыдущий узел
        current = current->next; // обновление указателя на текущий узел
    }
    newSub->data = intToAdd; // присваивание новому узлу значения
    newSub->next = current; // присваивание новому узлу указателя на текущий узел
    previous->next = newSub; // обновление указателя предыдущего узла на новый узел
    std::cout << "\nДобавлен элемент " << newSub->data << " во вспомогательный список\n";
}

// Функция добавления нового элемента во вспомогательный список после заданного
void subInsertAfter(int intToAdd, SubListItem *pTemp) {
    auto *newSub = new SubListItem; // создание нового узла вспомогательного списка
    newSub->data = intToAdd; // присваивание новому узлу значения
    newSub->next = pTemp->next; // присваивание новому узлу указателя на следующий узел
    pTemp->next = newSub; // обновление указателя текущего узла на новый узел
    std::cout << "\nДобавлен элемент " << newSub->data << " во вспомогательный список\n";
}

// Функция удаления элемента в главном списке
void mainRemove(const std::string &strToDel) {
    MainListItem *pTemp = head->pMainList; // указатель на первый элемент в главном списке
    MainListItem *pPrev = head; // указатель на голову главного списка
    while (pTemp != nullptr) { // проход по главному списку
        if (pTemp->dataStr == strToDel) { // если найден элемент с заданным значением
            SubListItem *pSub = pTemp->pSubList; // указатель на первый элемент вспомогательного списка
            while (pSub != nullptr) { // проход по вспомогательному списку
                SubListItem *pSubTemp = pSub; //  создание временной переменной pSubTemp
                pSub = pSub->next; // перемещение указателя pSub на следующий элемент списка
                delete pSubTemp; // удаление элемента вспомогательного списка
            }
            pPrev->pMainList = pTemp->pMainList; // переназначение указателя на предыдущий элемент главного списка
            delete pTemp; // удаление элемента главного списка
            std::cout << "\nУдален элемент " << strToDel << " из главного списка\n";
            break;
        }
        pPrev = pTemp; // сохранение указателя на предыдущий элемент списка pTemp в pPrev
        pTemp = pTemp->pMainList; // перемещение указателя pTemp на следующий элемент списка
    }
}

// Функция удаления элемента во вспомогательном списке
void subRemove(int intToDel, SubListItem *subHead) {
    // Установка указателей на начало списка и на его первый элемент
    SubListItem *pTemp = subHead->next;
    SubListItem *pPrev = subHead;
    // Поиск элемента, который нужно удалить
    while (pTemp != nullptr) {
        if (pTemp->data == intToDel) {
            pPrev->next = pTemp->next; // переподключение указателей для удаления элемента
            delete pTemp;
            std::cout << "\nУдален элемент " << intToDel << " из вспомогательного списка\n";
            break;
        }
        // Переход к следующему элементу
        pPrev = pTemp;
        pTemp = pTemp->next;
    }
}

// Функция для отображения текущего состояния списка
void printList() {
    MainListItem *currMain = head->pMainList; // устанавливаем текущий элемент на первый элемент главного списка
    while (currMain != nullptr) {
        std::cout << currMain->dataStr << ": ";
        SubListItem *currSub = currMain->pSubList; // устанавливаем текущий элемент на первый элемент вспомогательного списка
        if (subIsEmpty(currSub)) {
            std::cout << "пусто\n";
        } else {
            if (currSub->data == 0) { // проверяем, является ли первый элемент вспомогательного списка равным нулю
                currSub = currSub->next; // если да, переходим на следующий элемент
            }
            while (currSub != nullptr) { // выводим все элементы вспомогательного списка
                std::cout << currSub->data << " ";
                currSub = currSub->next;
            }
            std::cout << std::endl;
        }
        currMain = currMain->pMainList; // переходим к следующему элементу главного списка
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