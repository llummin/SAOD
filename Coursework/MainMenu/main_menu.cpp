#include "main_menu.h"
#include "../DataIO/data_io.h"
#include <iostream>
#include <limits>

void MainMenu::run() {
    int choice;
    do {
        displayMenu();
        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        processSelection(choice);
    } while (choice != 10);
}

void MainMenu::displayMenu() {
    std::cout << "---------------------------" << std::endl;
    std::cout << "Система управления школой" << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::cout << "1. Добавить класс" << std::endl;
    std::cout << "2. Удалить класс" << std::endl;
    std::cout << "3. Поиск класса" << std::endl;
    std::cout << "4. Добавить студента" << std::endl;
    std::cout << "5. Удалить студента" << std::endl;
    std::cout << "6. Поиск студента" << std::endl;
    std::cout << "7. Сохранить данные" << std::endl;
    std::cout << "8. Загрузить данные" << std::endl;
    std::cout << "9. Вывод школы" << std::endl;
    std::cout << "10. Выход" << std::endl;
    std::cout << "---------------------------" << std::endl;
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
            findClass();
            break;
        case 4:
            addStudent();
            break;
        case 5:
            removeStudent();
            break;
        case 6:
            searchStudent();
            break;
        case 7:
            saveData();
            break;
        case 8:
            loadData();
            break;
        case 9:
            traverseSchool();
            break;
        case 10:
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

void MainMenu::findClass() {
    std::string className;
    std::cout << "Введите название класса: ";
    std::getline(std::cin, className);

    Class *classObj = school.findClass(className);
    if (classObj) {
        std::cout << "Класс найден!: " << classObj->getClassName() << std::endl;
    } else {
        std::cout << "Класс не найден!" << std::endl;
    }
}

void MainMenu::addStudent() {
    std::string className;
    std::cout << "Введите название класса, чтобы добавить ученика: ";
    std::getline(std::cin, className);

    Class *classObj = school.findClass(className);
    if (classObj) {
        std::string name;
        int yearOfBirth;
        std::cout << "Введите имя студента: ";
        std::getline(std::cin, name);
        std::cout << "Введите год рождения ученика: ";
        std::cin >> yearOfBirth;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        classObj->addStudent(name, yearOfBirth);
        std::cout << "Ученик успешно добавлен!" << std::endl;
    } else {
        std::cout << "Класс не найден!" << std::endl;
    }
}

void MainMenu::removeStudent() {
    std::string className;
    std::cout << "Введите название класса, из которого нужно удалить учащегося: ";
    std::getline(std::cin, className);

    Class *classObj = school.findClass(className);
    if (classObj) {
        std::string name;
        std::cout << "Введите имя ученика, которого нужно удалить: ";
        std::getline(std::cin, name);

        classObj->removeStudent(name);
        std::cout << "Ученик успешно удален!" << std::endl;
    } else {
        std::cout << "Класс не найден!" << std::endl;
    }
}

void MainMenu::searchStudent() {
    std::string className;
    std::cout << "Введите название класса для поиска ученика: ";
    std::getline(std::cin, className);

    Class *classObj = school.findClass(className);
    if (classObj) {
        std::string name;
        std::cout << "Введите имя ученика для поиска: ";
        std::getline(std::cin, name);

        Student *student = classObj->findStudent(name);
        if (student) {
            std::cout << "Ученик найден: " << std::endl;
            std::cout << "Имя: " << student->getName() << std::endl;
            std::cout << "Год рождения: " << student->getYearOfBirth() << std::endl;
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
    std::cout << "Введите имя файла для загрузки данных: ";
    std::getline(std::cin, filename);

    DataIO::loadSchoolData(school, filename);
}

void MainMenu::traverseSchool() {
    std::cout << "Информация о школе:" << std::endl;
    std::cout << school.to_string() << std::endl;
}