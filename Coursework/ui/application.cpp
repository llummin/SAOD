#include "application.h"
#include <iostream>
#include <limits>

void Application::CaseShowMenu() {
    std::cout << "---------- Меню управления ----------" << std::endl;
    std::cout << "1. Создать школу" << std::endl;
    std::cout << "2. Добавить класс" << std::endl;
    std::cout << "3. Добавить ученика в класс" << std::endl;
    std::cout << "4. Поиск ученика" << std::endl;
    std::cout << "5. Удалить класс" << std::endl;
    std::cout << "6. Удалить ученика" << std::endl;
    std::cout << "7. Найти класс" << std::endl;
    std::cout << "8. Очистить структуру" << std::endl;
    std::cout << "9. Вывести структуру" << std::endl;
    std::cout << "10. Завершить работу" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
}

int Application::InputInteger() {
    std::string input;
    bool stop = false;
    int integer = -1;
    while (!stop) {
        try {
            std::cin >> input;
            integer = std::stoi(input);
            stop = true;
        } catch (const std::exception &) {
            std::cout << "Введите целое число: ";
        }
    }
    return integer;
}

void Application::AppCycle() {
    bool stop = false;
    CaseShowMenu();
    while (!stop) {
        switch (static_cast<Cases>(InputInteger())) {
            case Cases::Menu:
                CaseShowMenu();
                break;

            case Cases::AddSchool:
                CaseAddSchool();
                break;

            case Cases::AddClass:
                CaseAddClass();
                break;

            case Cases::AddStudent:
                CaseAddStudent();
                break;

            case Cases::SearchStudent:
                CaseSearchStudent();
                break;

            case Cases::DeleteClass:
                CaseDeleteClass();
                break;

            case Cases::DeleteStudent:
                CaseDeleteStudent();
                break;

            case Cases::SearchClass:
                CaseSearchClass();
                break;

            case Cases::ClearStructure:
                CaseClearStructure();
                break;

            case Cases::ShowStructure:
                CaseShowStructure();
                break;

            case Cases::Exit:
                CaseExit(stop);
                break;

            default:
                break;
        }
        std::cout << "0 - меню." << std::endl;
    }
}

void Application::CaseAddSchool() {
    if (school == nullptr) {
        std::string school_name;
        while (school_name.empty()) {
            std::cout << "Введите название школы: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, school_name);
        }
        school = new School(school_name);
        std::cout << "Школа создана." << std::endl;
    } else {
        std::cout << "Школа уже создана." << std::endl;
    }
}

void Application::CaseAddClass() {
    if (school != nullptr) {
        if (!school->IsFull()) {
            int class_number = -1;
            while (class_number < 0) {
                std::cout << "Введите номер класса: ";
                class_number = InputInteger();
            }
            if (school->SearchClass(class_number)) {
                std::cout << "Класс " << class_number << " уже есть в школе." << std::endl;
                return;
            } else {
                school->AddClass(class_number);
                std::cout << "Класс добавлена." << std::endl;
            }
            return;
        } else if (school->IsFull()) {
            std::cout << "Школа заполнена! Не более " << School::GetMaxNumberOfClasses() << " классов." << std::endl;
        }
    } else {
        std::cout << "Создайте школу." << std::endl;
    }
}

void Application::CaseAddStudent() {
    if (school != nullptr) {
        if (!school->IsEmpty()) {
            std::cout << "Введите номер класса в которую нужно добавить ученика: ";
            int class_number = InputInteger();
            bool check_search = false;
            int curr_class = 0;
            school->SearchClass(curr_class, class_number, check_search);
            if (check_search) {
                Class *pClass = school->GetClass(curr_class);
                std::string surname;
                while (surname.empty()) {
                    std::cout << "Введите Фамилию ученика: ";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::getline(std::cin, surname);
                }
                int yearOfBirth = -1;
                while (yearOfBirth < 0) {
                    std::cout << "Введите год рождения ученика: ";
                    yearOfBirth = InputInteger();
                }
                pClass->AddStudent(surname, yearOfBirth);
                std::cout << "Ученик добавлен." << std::endl;
            } else {
                std::cout << "Такого класса нет." << std::endl;
            }
        } else {
            std::cout << "Добавьте класс." << std::endl;
        }
    } else {
        std::cout << "Создайте школу." << std::endl;
    }
}

void Application::CaseDeleteClass() {
    if (school != nullptr) {
        if (!school->IsEmpty()) {
            std::cout << "Введите номер класса который нужно удалить: ";
            int class_number = InputInteger();
            bool check_search = false;
            int curr_class = 0;
            int prev_class = school->SearchClass(curr_class, class_number, check_search);
            if (check_search) {
                school->DeleteClass(prev_class, curr_class);
                std::cout << "Класс удален." << std::endl;
            } else {
                std::cout << "Такого класса нет." << std::endl;
            }
        }
    } else {
        std::cout << "Создайте школу." << std::endl;
    }
}

void Application::CaseSearchStudent() {
    if (school != nullptr) {
        if (!school->IsEmpty()) {
            std::cout << "Введите номер класса: ";
            int class_number = InputInteger();
            bool check_search = false;
            int curr_class = 0;
            school->SearchClass(curr_class, class_number, check_search);
            if (check_search) {
                std::string surname;
                while (surname.empty()) {
                    std::cout << "Введите фамилию ученика: ";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::getline(std::cin, surname);
                }
                Class *pClass = school->GetClass(curr_class);
                Student *student = pClass->SearchStudent(surname);
                if (student != nullptr) {
                    std::cout << "Ученик найден:" << std::endl;
                    std::cout << "Фамилия: " << student->GetSurname() << std::endl;
                    std::cout << "Год рождения: " << student->GetDateOfBirth() << std::endl;
                } else {
                    std::cout << "Ученик с указанной фамилией не найден." << std::endl;
                }
            } else {
                std::cout << "Такого класса нет." << std::endl;
            }
        } else {
            std::cout << "Добавьте класс." << std::endl;
        }
    } else {
        std::cout << "Создайте школу." << std::endl;
    }
}

void Application::CaseDeleteStudent() {
    if (school != nullptr) {
        if (!school->IsEmpty()) {
            std::cout << "Введите номер класса, из которого нужно удалить ученика: ";
            int class_number = InputInteger();
            bool check_search = false;
            int curr_class = 0;
            school->SearchClass(curr_class, class_number, check_search);
            if (check_search) {
                Class *pClass = school->GetClass(curr_class);
                std::string surname;
                while (surname.empty()) {
                    std::cout << "Введите фамилию ученика, которого нужно удалить: ";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::getline(std::cin, surname);
                }
                // Поиск студента, которого нужно удалить
                Student *target = pClass->SearchStudent(surname);
                if (target != nullptr) {
                    // Удаление указанного ученика
                    if (pClass->DeleteStudent(target)) {
                        std::cout << "Ученик удален." << std::endl;
                    } else {
                        std::cout << "Ошибка при удалении ученика." << std::endl;
                    }
                } else {
                    std::cout << "Ученик с указанной фамилией не найден." << std::endl;
                }
            } else {
                std::cout << "Такого класса не существует." << std::endl;
            }
        } else {
            std::cout << "Добавьте класс." << std::endl;
        }
    } else {
        std::cout << "Создайте школу." << std::endl;
    }
}

void Application::CaseSearchClass() {
    if (school != nullptr) {
        if (!school->IsEmpty()) {
            std::cout << "Введите номер класса: ";
            int class_number = InputInteger();
            bool check_search = false;
            int curr_class = 0;
            school->SearchClass(curr_class, class_number, check_search);
            if (check_search) {
                std::cout << "Класс найден." << std::endl;
                school->GetClass(curr_class)->ShowClass();
            } else {
                std::cout << "Такого класса нет." << std::endl;
            }
        }
    } else {
        std::cout << "Создайте школу." << std::endl;
    }
}

void Application::CaseClearStructure() {
    if (school != nullptr) {
        school->ClearMemory();
        delete school;
        school = nullptr;
        std::cout << "Структура очищена." << std::endl;
    } else {
        std::cout << "Нет данных для очистки." << std::endl;
    }
}

void Application::CaseShowStructure() {
    if (school != nullptr) {
        school->ShowClasses();
    } else {
        std::cout << "Создайте школу." << std::endl;
    }
}

void Application::CaseExit(bool &stop) {
    stop = true;
    if (school != nullptr) {
        school->ClearMemory();
        delete school;
        school = nullptr;
    }
}