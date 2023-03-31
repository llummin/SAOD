// ������������ ������ �8 (������ 1, ���� 4, ����� 3) - ������ ������� �� ������ ��������� ������������� ������

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

// ������� ������������� ������ �������
void initList(MainListItem *&headItem) {
    headItem->pMainList = nullptr;
    headItem->pSubList = nullptr;
    headItem->dataStr = " ";
}

// ������� �������� �������� ������ �� �������
bool mainIsEmpty(MainListItem *headItem) {
    return headItem->pMainList == nullptr;
}

// ������� �������� ���������������� ������ �� �������
bool subIsEmpty(SubListItem *headItem) {
    return headItem->next == nullptr;
}

// ���� �������������� �������� � ���������
int failure() {
    int choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "\n������� ������ ���������: ";
            continue;
        }
        std::cin.ignore(32767, '\n');
        break;
    }
    return choice;
}

// ���� �������������� �������� � ��������� ���������
int failure(int begin, int end) {
    int choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "\n������� ������ ���������: ";
            continue;
        }
        std::cin.ignore(32767, '\n');
        if (choice < begin || choice > end) {
            std::cout << "\n������� ������ ���������: ";
            continue;
        }
        break;
    }
    return choice;
}

// ���� ������ � ��������� �� �������
std::string checkStringNotEmpty() {
    std::string str;
    bool is_space;
    while (true) {
        getline(std::cin, str);
        if (str.empty()) {
            std::cout << "�� ����� ������ ������. ���������� ��� ���: ";
        } else {
            is_space = true;
            for (char i: str) {
                if (!isspace(i)) {
                    is_space = false;
                    break;
                }
            }
            if (is_space) {
                std::cout << "�� ����� ������ ������. ���������� ��� ���: ";
            } else {
                return str;
            }
        }
    }
}

// ����� � ������� ������
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

// ����� �� ��������������� ������
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

// ����� � ������
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

// ������� ���������� ������ �������� ����� �������� � ������� ������
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
    std::cout << "\n�������� ������� " << newItem->dataStr << " � ������� ������\n";
}

// ������� ���������� ������ �������� ����� ��������� � ������� ������
void mainInsertAfter(std::string strToAdd, MainListItem *pTemp) {
    auto *newItem = new MainListItem;
    auto *newSub = new SubListItem;
    newSub->data = 0;
    newSub->next = nullptr;
    newItem->dataStr = std::move(strToAdd);
    newItem->pMainList = pTemp->pMainList;
    newItem->pSubList = newSub;
    pTemp->pMainList = newItem;
    std::cout << "\n�������� ������� " << newItem->dataStr << " � ������� ������\n";
}

// ������� ���������� ������ �������� �� ��������������� ������ ����� ��������
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
    std::cout << "\n�������� ������� " << newSub->data << " �� ��������������� ������\n";
}

// ������� ���������� ������ �������� �� ��������������� ������ ����� ���������
void subInsertAfter(int intToAdd, SubListItem *pTemp) {
    auto *newSub = new SubListItem;
    newSub->data = intToAdd;
    newSub->next = pTemp->next;
    pTemp->next = newSub;
    std::cout << "\n�������� ������� " << newSub->data << " �� ��������������� ������\n";
}

// ������� ��� ����������� �������� ��������� ������
void printList() {
    MainListItem *currMain = head->pMainList;
    while (currMain != nullptr) {
        std::cout << currMain->dataStr << ": ";
        SubListItem *currSub = currMain->pSubList;
        if (subIsEmpty(currSub)) {
            std::cout << "�����\n";
        } else {
            // ��������, �������� �� ������ ������� ���������������� ������ ������ ����
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

// �������� ����
void callMenu(MainListItem *&headItem) {
    bool work{true};
    int choice;
    while (work) {
        std::cout << "_______________________________________________________________________";
        std::cout << "\n������� ����� �������: \n";
        std::cout << "1. ������� ������� ��������� ������ �������\n";
        std::cout << "2. ���������� �������� � ������� ������ ����� ��������\n";
        std::cout << "3. ���������� �������� � ������� ������ ����� ���������\n";
        std::cout << "4. ���������� �������� �� ��������������� ������ ����� ��������\n";
        std::cout << "5. ���������� �������� �� ��������������� ������ ����� ���������\n";
        std::cout << "6. ����� �������� � ������� ������\n";
        std::cout << "7. ����� �������� �� ��������������� ������ \n";
        std::cout << "8. ���������� ������\n";
        std::cout << "_______________________________________________________________________\n";
        std::cout << "������� ����� �������: ";
        choice = failure(1, 8);
        MainListItem *pMain;
        SubListItem *pSub;
        std::string strToBefore;
        int intToBefore;
        switch (choice) {
            case 1:
                if (mainIsEmpty(headItem)) {
                    std::cout << "\n������ ����!\n";
                } else {
                    std::cout << "\n������:\n";
                    printList();
                }
                break;
            case 2:
                if (mainIsEmpty(headItem)) {
                    std::cout << "\n������� �������� ������, ������� ������ �� ��������: ";
                    mainInsertAfter(checkStringNotEmpty(), headItem);
                    break;
                }
                std::cout << "\n������� �������, ����� ������� ������ �������� �����: ";
                strToBefore = checkStringNotEmpty();
                pMain = mainSearch(strToBefore);
                if (pMain == nullptr) {
                    std::cout << "\n������ �������� � ������� ������ �� ����������.\n";
                    break;
                }
                std::cout << "\n������� �������� ������, ������� ������ �� ��������: ";
                mainInsertBefore(checkStringNotEmpty(), strToBefore);
                break;
            case 3:
                if (mainIsEmpty(headItem)) {
                    std::cout << "\n������� �������� ������, ������� ������ �� ��������: ";
                    mainInsertAfter(checkStringNotEmpty(), headItem);
                    break;
                }
                std::cout << "\n������� �������, ����� ������� ������ �������� �����: ";
                pMain = mainSearch(checkStringNotEmpty());
                if (pMain == nullptr) {
                    std::cout << "\n������ �������� � ������� ������ �� ����������.\n";
                    break;
                }
                std::cout << "\n������� �������� ������, ������� ������ �� ��������: ";
                mainInsertAfter(checkStringNotEmpty(), pMain);
                break;
            case 4:
                if (mainIsEmpty(headItem)) {
                    std::cout << "\n������� ������ ����! ���������� �� ��������������� ����������!\n";
                    break;
                }
                std::cout << "\n������� �������� ������, � ������� ������ �� �������� ����� �������: ";
                pMain = mainSearch(checkStringNotEmpty());
                if (pMain == nullptr) {
                    std::cout << "\n������ �������� �������� ������ �� ����������.\n";
                    break;
                }
                if (subIsEmpty(pMain->pSubList)) {
                    std::cout << "\n������� �����, ������� ������ �� �������� �� ��������������� ������: ";
                    subInsertAfter(failure(), pMain->pSubList);
                    break;
                }

                std::cout << "\n������� �������, ����� ������� ������ �������� �����: ";
                intToBefore = failure();
                pSub = searchInList(intToBefore, pMain->pSubList);
                if (pSub == nullptr) {
                    std::cout << "\n������ �������� �������� ������ �� ����������.\n";
                    break;
                }
                std::cout << "\n������� �����, ������� ������ �� �������� �� ��������������� ������: ";
                subInsertBefore(failure(), pMain->pSubList, intToBefore);
                break;
            case 5:
                if (mainIsEmpty(headItem)) {
                    std::cout << "\n������� ������ ����! ���������� �� ��������������� ����������!\n";
                    break;
                }
                std::cout << "\n������� �������� ������, � ������� ������ �� �������� ����� �������: ";
                pMain = mainSearch(checkStringNotEmpty());
                if (pMain == nullptr) {
                    std::cout << "\n������ �������� �������� ������ �� ����������.\n";
                    break;
                }
                if (subIsEmpty(pMain->pSubList)) {
                    std::cout << "\n������� �����, ������� ������ �� �������� �� ��������������� ������: ";
                    subInsertAfter(failure(), pMain->pSubList);
                    break;
                }

                std::cout << "\n������� �������, ����� �������� ������ �������� �����: ";
                pSub = searchInList(failure(), pMain->pSubList);
                if (pSub == nullptr) {
                    std::cout << "\n������ �������� �������� ������ �� ����������.\n";
                    break;
                }
                std::cout << "\n������� �����, ������� ������ �� �������� �� ��������������� ������: ";
                subInsertAfter(failure(), pSub);
                break;
            case 6: {
                if (mainIsEmpty(head)) {
                    std::cout << "\n������� ������ ����! ����� ����������!\n";
                    break;
                }
                std::cout << "\n������� �������� �������� ������: ";
                MainListItem *foundMain = mainSearch(checkStringNotEmpty());
                if (foundMain == nullptr) {
                    std::cout << "\n������ ������ �� ������.\n";
                    break;
                }
                int index = 0;
                MainListItem *cur = head->pMainList;
                while (cur != foundMain) {
                    index++;
                    cur = cur->pMainList;
                }
                std::cout << "\n������ ������ ������. ������ �������� � ������� ������: " << index << std::endl;
                break;
            }
            case 7: {
                if (mainIsEmpty(head)) {
                    std::cout << "\n������� ������ ����! ����� ����������!\n";
                    break;
                }
                std::cout << "\n������� �������� �������� ������: ";
                MainListItem *foundMain = mainSearch(checkStringNotEmpty());
                if (foundMain == nullptr) {
                    std::cout << "\n������ ������ �� ������.\n";
                    break;
                }
                if (subIsEmpty(foundMain->pSubList)) {
                    std::cout << "\n��������������� ������ ����! ����� ����������!\n";
                    break;
                }
                std::cout << "\n������� ������������� �������� ��� ������: ";
                int intToSearch = failure();
                SubListItem *foundSub = subSearch(intToSearch);
                if (foundSub == nullptr) {
                    std::cout << "\n������ ������� �� ������.\n";
                    break;
                }
                int subIndex = 0;
                SubListItem *subCur = foundMain->pSubList->next;
                while (subCur != foundSub) {
                    subIndex++;
                    subCur = subCur->next;
                }
                std::cout << "\n������ ������� ������. ������ �������� �� ��������������� ������: " << subIndex
                          << std::endl;
                break;
            }
            case 8:
                work = false;
                std::cout << "\n��������� ���������\n";
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