#include "application.h"
#include "../data_management/data_manager.h"
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
        std::cout << "\nШкола успешно создана!" << std::endl;
    } else {
        std::cout << "\nШкола уже создана!" << std::endl;
    }
}

void Application::AddClass() {
    if (school == nullptr) {
        std::cout << "\nШкола не создана. Сначала создайте школу!" << std::endl;
        return;
    }

    std::cout << "Введите название класса: ";
    std::string className;
    std::getline(std::cin, className);

    auto *newClass = new Class(className);
    school->AddClass(newClass);
}

void Application::SearchClass() {
    if (school == nullptr) {
        std::cout << "\nШкола не создана. Сначала создайте школу!" << std::endl;
        return;
    }

    std::cout << "Введите название класса для поиска: ";
    std::string className;
    std::getline(std::cin, className);

    Class *foundClass = school->SearchClass(className);
    if (foundClass != nullptr) {
        std::cout << "Класс '" << foundClass->GetClassName() << "' найден" << std::endl;
    } else {
        std::cout << "Класс '" << className << "' не найден." << std::endl;
    }
}

void Application::DeleteClass() {
    if (school == nullptr) {
        std::cout << "\nШкола не создана. Сначала создайте школу!" << std::endl;
        return;
    }

    std::cout << "Введите название класса для удаления: ";
    std::string className;
    std::getline(std::cin, className);

    Class *classToDelete = school->SearchClass(className);
    if (classToDelete != nullptr) {
        std::string deletedClassName = classToDelete->GetClassName();
        school->DeleteClass(classToDelete);
        std::cout << "Класс '" << deletedClassName << "' успешно удален." << std::endl;
    } else {
        std::cout << "Класс '" << className << "' не найден и не может быть удален." << std::endl;
    }
}

void Application::AddStudent() {
    if (school != nullptr) {
        std::cout << "Введите название класса, в который следует добавить ученика: ";
        std::string className;
        std::getline(std::cin, className);

        Class *pClass = school->SearchClass(className);
        if (pClass != nullptr) {
            std::string surname;
            while (surname.empty()) {
                std::cout << "Введите фамилию ученика: ";
                std::getline(std::cin, surname);
            }
            int yearOfBirth = -1;
            while (yearOfBirth < 0) {
                std::cout << "Введите год рождения ученика: ";
                yearOfBirth = GetIntInput();
            }
            pClass->AddStudent(surname, yearOfBirth);
            std::cout << "\nУченик успешно добавлен в класс!" << std::endl;
        } else {
            std::cout << "Данный класс не найден!" << std::endl;
        }
    } else {
        std::cout << "\nШкола не создана. Сначала создайте школу!" << std::endl;
    }
}

void Application::SearchStudent() {
    if (school != nullptr) {
        std::cout << "Введите название класса, в котором вы хотите найти ученика: ";
        std::string className;
        std::getline(std::cin, className);

        Class *pClass = school->SearchClass(className);
        if (pClass != nullptr) {
            std::string surname;
            while (surname.empty()) {
                std::cout << "Введите фамилию ученика: ";
                std::getline(std::cin, surname);
            }

            Student *student = pClass->SearchStudent(surname);
            if (student != nullptr) {
                std::cout << "\nУченик найден:" << std::endl;
                std::cout << "Фамилия: " << student->GetSurname() << std::endl;
                std::cout << "Год рождения: " << student->GetDateOfBirth() << std::endl;
            } else {
                std::cout << "\nУченик с указанной фамилией не найден!" << std::endl;
            }
        } else {
            std::cout << "\nДанный класс не найден. Пожалуйста, проверьте правильность ввода." << std::endl;
        }
    } else {
        std::cout << "\nШкола не создана. Сначала создайте школу!" << std::endl;
    }
}

void Application::DeleteStudent() {
    if (school != nullptr) {
        std::cout << "Введите название класса, из которого нужно удалить ученика: ";
        std::string className;
        std::getline(std::cin, className);

        Class *pClass = school->SearchClass(className);
        if (pClass != nullptr) {
            std::string surname;
            while (surname.empty()) {
                std::cout << "Введите фамилию ученика, которого нужно удалить: ";
                std::getline(std::cin, surname);
            }

            Student *target = pClass->SearchStudent(surname);
            if (target != nullptr) {
                if (pClass->DeleteStudent(target)) {
                    std::cout << "\nУченик успешно удален из класса!" << std::endl;
                }
            } else {
                std::cout << "\nУченик с указанной фамилией не найден в данном классе!" << std::endl;
            }
        } else {
            std::cout << "\nДанный класс не найден. Пожалуйста, проверьте правильность ввода." << std::endl;
        }
    } else {
        std::cout << "\nШкола не создана. Сначала создайте школу!" << std::endl;
    }
}

void Application::ClearStructure() {
    if (school == nullptr) {
        std::cout << "\nШкола не создана. Сначала создайте школу!" << std::endl;
        return;
    }

    school->SchoolClearMemory();
    delete school;
    school = nullptr;
    std::cout << "\nСтруктура данных очищена." << std::endl;
}

void Application::ShowStructure() {
    if (school == nullptr) {
        std::cout << "\nШкола не создана. Сначала создайте школу!" << std::endl;
        return;
    }

    school->ShowSchoolStructure();
    std::cout << std::endl;
}

void Application::SaveData() {
    if (school == nullptr) {
        std::cout << "\nШкола не создана. Сначала создайте школу!" << std::endl;
        return;
    }

    std::string filename;
    std::cout << "Введите имя файла для сохранения данных: ";
    std::getline(std::cin, filename);

    if (DataManager::SaveToFile(*school, filename)) {
        std::cout << "\nДанные успешно сохранены в файл: " << filename << std::endl;
    } else {
        std::cout << "\nНе удалось сохранить данные в файл: " << filename << std::endl;
    }
}

void Application::LoadData() {
    std::string filename;
    std::cout << "Введите имя файла для загрузки данных: ";
    std::getline(std::cin, filename);

    if (DataManager::LoadFromFile(school, filename)) {
        std::cout << "\nДанные успешно загружены из файла: " << filename << std::endl;
    } else {
        std::cout << "\nНе удалось загрузить данные из файла: " << filename << std::endl;
    }
}

void Application::Exit(bool &stop) {
    std::cout << "Выход из программы..." << std::endl;
    stop = false;
}

void Application::ShowMenu() {
    std::cout << "_____________________________________________" << std::endl;
    std::cout << "1. Создать школу" << std::endl;
    std::cout << "2. Добавить класс в школу" << std::endl;
    std::cout << "3. Найти класс в школе" << std::endl;
    std::cout << "4. Удалить класс из школы" << std::endl;
    std::cout << "5. Добавить ученика в класс" << std::endl;
    std::cout << "6. Найти ученика в классе" << std::endl;
    std::cout << "7. Удалить ученика из класса" << std::endl;
    std::cout << "8. Очистить структуру" << std::endl;
    std::cout << "9. Вывод всей структуры" << std::endl;
    std::cout << "10. Сохранить данные" << std::endl;
    std::cout << "11. Загрузить данные" << std::endl;
    std::cout << "12. Завершение работы" << std::endl;
    std::cout << "_____________________________________________" << std::endl;
    std::cout << "Введите номер команды: ";
}

void Application::Run() {
    bool running = true;
    while (running) {
        ShowMenu();
        int choice = GetIntInputWithRange(1, 12);
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
            case Cases::SaveData:
                SaveData();
                break;
            case Cases::LoadData:
                LoadData();
                break;
            case Cases::Exit:
                Exit(running);
                break;
            default:
                break;
        }
    }
}
