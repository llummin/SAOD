#include "application.h"
#include <iostream>
#include <limits>

int Application::GetIntInput() {
    int choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Введите данные правильно: ";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break;
    }
    return choice;
}

int Application::GetIntInputWithRange(int begin, int end) {
    int choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Введите данные правильно: ";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (choice < begin || choice > end) {
            std::cout << "Введите данные правильно: ";
            continue;
        }
        break;
    }
    return choice;
}

void Application::AddSchool() {
    if (school == nullptr) {
        int school_number = 0;
        while (school_number == 0) {
            std::cout << "\nВведите номер школы: ";
            school_number = GetIntInput();
        }
        school = new School(school_number);
        std::cout << "\nШкола успешно создана!\n" << std::endl;
    } else {
        std::cout << "\nШкола уже создана!\n" << std::endl;
    }
}

void Application::AddClass() {
    if (school == nullptr) {
        std::cout << "Сначала создайте школу!" << std::endl;
        return;
    }

    int school_number = school->GetSchoolNumber();
    school = School::GetInstance(school_number);

    std::cout << "Введите название класса: ";
    std::string className;
    std::cin.ignore();
    std::getline(std::cin, className);

    auto *newClass = new Class(className);
    school->AddClass(newClass);
}

void Application::SearchClass() {
    if (school == nullptr) {
        std::cout << "Сначала создайте школу!" << std::endl;
        return;
    }

    int school_number = school->GetSchoolNumber();
    school = School::GetInstance(school_number);

    std::cout << "Введите название класса для поиска: ";
    std::string className;
    std::cin.ignore();
    std::getline(std::cin, className);

    Class *foundClass = school->SearchClass(className);
    if (foundClass != nullptr) {
        std::cout << "Класс найден: " << foundClass->GetClassName() << std::endl;
    } else {
        std::cout << "Класс не найден." << std::endl;
    }
}

void Application::DeleteClass() {
    if (school == nullptr) {
        std::cout << "Сначала создайте школу!" << std::endl;
        return;
    }

    int school_number = school->GetSchoolNumber();
    school = School::GetInstance(school_number);

    std::cout << "Введите название класса для удаления: ";
    std::string className;
    std::cin.ignore();
    std::getline(std::cin, className);

    Class *classToDelete = school->SearchClass(className);
    if (classToDelete != nullptr) {
        school->DeleteClass(classToDelete);
        delete classToDelete;
        std::cout << "Класс удален." << std::endl;
    } else {
        std::cout << "Класс не найден." << std::endl;
    }
}

void Application::AddStudent() {
    if (school != nullptr) {
        if (!school->IsEmpty()) {
            std::cout << "\nВведите номер класса, в который следует добавить ученика: ";
            int class_number = GetIntInput();
            bool check_search = false;
            int curr_class = 0;
            school->SearchClass(curr_class, class_number, check_search);
            if (check_search) {
                Class *pClass = school->GetClass(curr_class);
                std::string surname;
                while (surname.empty()) {
                    std::cout << "Введите фамилию ученика: ";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::getline(std::cin, surname);
                }
                int yearOfBirth = -1;
                while (yearOfBirth < 0) {
                    std::cout << "Введите год рождения ученика: ";
                    yearOfBirth = GetIntInput();
                }
                pClass->AddStudent(surname, yearOfBirth);
                std::cout << "\nУченик успешно добавлен в класс!\n" << std::endl;
            } else {
                std::cout << "\nДанный класс не создан. Создайте класс!\n" << std::endl;
            }
        } else {
            std::cout << "\nКласс не создан. Создайте класс!\n" << std::endl;
        }
    } else {
        std::cout << "\nШкола не создана. Создайте школу!\n" << std::endl;
    }
}

void Application::SearchStudent() {
    if (school != nullptr) {
        if (!school->IsEmpty()) {
            std::cout << "\nВведите номер класса: ";
            int class_number = GetIntInput();
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
                    std::cout << "\nУченик найден:" << std::endl;
                    std::cout << "Фамилия: " << student->GetSurname() << std::endl;
                    std::cout << "Год рождения: " << student->GetDateOfBirth() << std::endl;
                } else {
                    std::cout << "\nУченик с указанной фамилией не найден!\n" << std::endl;
                }
            } else {
                std::cout << "\nДанный класс не создан. Создайте класс!\n" << std::endl;
            }
        } else {
            std::cout << "\nКласс не создан. Создайте класс!\n" << std::endl;
        }
    } else {
        std::cout << "\nШкола не создана. Создайте школу!\n" << std::endl;
    }
}

void Application::DeleteStudent() {
    if (school != nullptr) {
        if (!school->IsEmpty()) {
            std::cout << "\nВведите номер класса, из которого нужно удалить ученика: ";
            int class_number = GetIntInput();
            bool check_search = false;
            int curr_class = 0;
            school->SearchClass(curr_class, class_number, check_search);
            if (check_search) {
                Class *pClass = school->GetClass(curr_class);
                std::string surname;
                while (surname.empty()) {
                    std::cout << "\nВведите фамилию ученика, которого нужно удалить: ";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::getline(std::cin, surname);
                }
                Student *target = pClass->SearchStudent(surname);
                if (target != nullptr) {
                    if (pClass->DeleteStudent(target)) {
                        std::cout << "\nУченик успешно удален из класса!\n" << std::endl;
                    }
                } else {
                    std::cout << "\nУченик с указанной фамилией не найден!\n" << std::endl;
                }
            } else {
                std::cout << "\nДанный класс не создан. Создайте класс!\n" << std::endl;
            }
        } else {
            std::cout << "\nКласс не создан. Создайте класс!\n" << std::endl;
        }
    } else {
        std::cout << "\nШкола не создана. Создайте школу!\n" << std::endl;
    }
}

void Application::ClearStructure() {
    if (school == nullptr) {
        std::cout << "Сначала создайте школу!" << std::endl;
        return;
    }

    int school_number = school->GetSchoolNumber();
    school = School::GetInstance(school_number);
    school->SchoolClearMemory();
    std::cout << "Структура данных очищена." << std::endl;
}

void Application::ShowStructure() {
    if (school == nullptr) {
        std::cout << "Сначала создайте школу!" << std::endl;
        return;
    }

    int school_number = school->GetSchoolNumber();
    school = School::GetInstance(school_number);
    school->ShowSchool();
}

void Application::Exit(bool &stop) {
    std::cout << "Выход из программы." << std::endl;
    stop = true;
}

void Application::ShowMenu() {
    std::cout << "__________Меню управления__________" << std::endl;
    std::cout << "1. Создать школу" << std::endl;
    std::cout << "2. Добавить класс в школу" << std::endl;
    std::cout << "3. Найти класс в школе" << std::endl;
    std::cout << "4. Удалить класс из школы" << std::endl;
    std::cout << "5. Добавить ученика в класс" << std::endl;
    std::cout << "6. Найти ученика в классе" << std::endl;
    std::cout << "7. Удалить ученика из класса" << std::endl;
    std::cout << "8. Очистить структуру" << std::endl;
    std::cout << "9. Вывод всей структуры" << std::endl;
    std::cout << "10. Завершение работы" << std::endl;
    std::cout << "___________________________________" << std::endl;
    std::cout << "Введите номер команды: ";
}

void Application::Run() {
    bool running = true;
    while (running) {
        ShowMenu();
        int choice = GetIntInputWithRange(1, 10);
        switch (static_cast<Cases>(choice)) {
            case Cases::Menu:
                ShowMenu();
                break;
            case Cases::AddSchool:
                AddSchool();
                break;
            case Cases::AddClass:
                AddClass();
                break;
            case Cases::SearchClass:
                SearchClass();
                break;
            case Cases::DeleteClass:
                DeleteClass();
                break;
            case Cases::AddStudent:
                AddStudent();
                break;
            case Cases::SearchStudent:
                SearchStudent();
                break;
            case Cases::DeleteStudent:
                DeleteStudent();
                break;
            case Cases::ClearStructure:
                ClearStructure();
                break;
            case Cases::ShowStructure:
                ShowStructure();
                break;
            case Cases::Exit:
                Exit(running);
                break;
            default:
                break;
        }
    }
}