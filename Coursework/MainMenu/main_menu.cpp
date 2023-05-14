#include <iostream>
#include "main_menu.h"

void MainMenu::run() {
    int choice = 0;

    while (choice != 7) {
        displayMenu();

        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;
        std::cin.ignore();

        processSelection(choice);
    }
}

void MainMenu::displayMenu() {
    std::cout << "=========== ГЛАВНОЕ МЕНЮ ===========" << std::endl;
    std::cout << "1. Добавить класс" << std::endl;
    std::cout << "2. Удалить класс" << std::endl;
    std::cout << "3. Добавить студента" << std::endl;
    std::cout << "4. Удалить студента" << std::endl;
    std::cout << "5. Поиск студента" << std::endl;
    std::cout << "6. Сохранить данные" << std::endl;
    std::cout << "7. Загрузить данные" << std::endl;
    std::cout << "8. Выход" << std::endl;
    std::cout << "=================================" << std::endl;
}

void MainMenu::processSelection(int choice) {
    switch (choice) {
        case 1:
            addClass();
            break;
        case 2:
            removeClass();
            break;
        case 3:
            addStudent();
            break;
        case 4:
            removeStudent();
            break;
        case 5:
            searchStudent();
            break;
        case 6:
            saveData();
            break;
        case 7:
            loadData();
            break;
        case 8:
            std::cout << "Завершение программы..." << std::endl;
            break;
        default:
            std::cout << "Неверный выбор. Пожалуйста, попробуйте еще раз." << std::endl;
            break;
    }
}

void MainMenu::addClass() {
    std::string className;
    std::cout << "Введите название класса: ";
    std::getline(std::cin, className);

    school.addClass(className);
    std::cout << "Класс успешно добавлен!" << std::endl;
}

void MainMenu::removeClass() {
    std::string className;
    std::cout << "Введите название класса: ";
    std::getline(std::cin, className);

    school.removeClass(className);
    std::cout << "Класс успешно удален!" << std::endl;
}

void MainMenu::addStudent() {
    std::string className;
    std::cout << "Введите название класса: ";
    std::getline(std::cin, className);

    Class* classObj = school.findClass(className);
    if (classObj) {
        std::string name;
        int yearOfBirth;
        std::cout << "Введите имя ученика: ";
        std::getline(std::cin, name);
        std::cout << "Введите год рождения ученика: ";
        std::cin >> yearOfBirth;
        std::cin.ignore();

        classObj->addStudent(name, yearOfBirth);
        std::cout << "Ученик успешно добавлен!" << std::endl;
    } else {
        std::cout << "Класс не найден!" << std::endl;
    }
}

void MainMenu::removeStudent() {
    std::string className;
    std::cout << "Введите название класса: ";
    std::getline(std::cin, className);

    Class* classObj = school.findClass(className);
    if (classObj) {
        std::string name;
        std::cout << "Введите имя ученика: ";
        std::getline(std::cin, name);

        classObj->removeStudent(name);
        std::cout << "Ученик успешно удален!" << std::endl;
    } else {
        std::cout << "Класс не найден!" << std::endl;
    }
}

void MainMenu::searchStudent() {
    std::string className;
    std::cout << "Введите название класса: ";
    std::getline(std::cin, className);

    Class* classObj = school.findClass(className);
    if (classObj) {
        std::string name;
        std::cout << "Введите имя ученика: ";
        std::getline(std::cin, name);

        Student* student = classObj->findStudent(name);
        if (student) {
            std::cout << "Ученик найден. Год рождения: " << student->getYearOfBirth() << std::endl;
        } else {
            std::cout << "Ученик не найден!" << std::endl;
        }
    } else {
        std::cout << "Класс не найден!" << std::endl;
    }
}

void MainMenu::saveData() {
    std::string filename;
    std::cout << "Введите имя файла для сохранения данных: ";
    std::getline(std::cin, filename);

    DataIO::saveSchoolData(school, filename);
}

void MainMenu::loadData() {
    std::string filename;
    std::cout << "Введите имя файла для загрузки данных из: ";
    std::getline(std::cin, filename);

    DataIO::loadSchoolData(school, filename);
}