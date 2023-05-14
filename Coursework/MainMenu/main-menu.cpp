#include <iostream>
#include "main-menu.h"

MainMenu::MainMenu() {
    // TODO: Инициализировать объект школы
}

void MainMenu::startMenu() {
    int choice = 0;
    while (choice != 8) {
        displayMenu();
        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;
        std::cin.ignore();

        processInput(choice);
    }
}

void MainMenu::displayMenu() {
    std::cout << "-------------------------" << std::endl;
    std::cout << "      ГЛАВНОЕ МЕНЮ" << std::endl;
    std::cout << "-------------------------" << std::endl;
    std::cout << "1. Добавить класс" << std::endl;
    std::cout << "2. Удалить класс" << std::endl;
    std::cout << "3. Добавить студента" << std::endl;
    std::cout << "4. Удалить студента" << std::endl;
    std::cout << "5. Поиск студента" << std::endl;
    std::cout << "6. Сохранить данные" << std::endl;
    std::cout << "7. Загрузить данные" << std::endl;
    std::cout << "8. Выход" << std::endl;
    std::cout << "-------------------------" << std::endl;
}

void MainMenu::processInput(int choice) {
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
    std::cout << "Введите название класса для удаления: ";
    std::getline(std::cin, className);

    school.removeClass(className);
    std::cout << "Класс успешно удален!" << std::endl;
}

void MainMenu::addStudent() {
    std::string className;
    std::cout << "Введите название класса, чтобы добавить ученика: ";
    std::getline(std::cin, className);

    Class *classObj = school.findClass(className);
    if (classObj) {
        std::string studentName;
        std::cout << "Введите имя ученика: ";
        std::getline(std::cin, studentName);

        int yearOfBirth;
        std::cout << "Введите год рождения ученика: ";
        std::cin >> yearOfBirth;
        std::cin.ignore();

        classObj->addStudent(studentName, yearOfBirth);
        std::cout << "Ученик успешно добавлен!" << std::endl;
    } else {
        std::cout << "Класс не найден!" << std::endl;
    }
}

void MainMenu::removeStudent() {
    std::string className;
    std::cout << "Введите название класса, чтобы удалить ученика: ";
    std::getline(std::cin, className);

    Class *classObj = school.findClass(className);
    if (classObj) {
        std::string studentName;
        std::cout << "Введите имя ученика, которого нужно удалить: ";
        std::getline(std::cin, studentName);

        Student *student = classObj->findStudent(studentName);
        if (student) {
            classObj->removeStudent(studentName);
            std::cout << "Ученик успешно удален!" << std::endl;
        } else {
            std::cout << "Ученик не найден!" << std::endl;
        }
    } else {
        std::cout << "Класс не найден!" << std::endl;
    }
}

void MainMenu::searchStudent() {
    // TODO: Реализовать поиск студента в школе
}

void MainMenu::saveData() {
    // TODO: Реализовать сохранение данных школы в файл
}

void MainMenu::loadData() {
    // TODO: Реализовать загрузку данных школы из файла
}