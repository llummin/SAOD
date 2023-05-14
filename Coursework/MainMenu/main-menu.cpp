#include <iostream>
#include "main-menu.h"

MainMenu::MainMenu() {
    // TODO: Инициализировать объект школы
}

void MainMenu::startMenu() {
    int choice = 0;
    while (choice != 9) {
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
    std::cout << "9. Выход" << std::endl;
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
        case 9:
            std::cout << "Выход из программы..." << std::endl;
            break;
        default:
            std::cout << "Неверный выбор! Пожалуйста, попробуйте еще раз." << std::endl;
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
    int classNumber;
    std::cout << "Введите номер класса для удаления: ";
    std::cin >> classNumber;

    school.removeClass(classNumber);
    std::cout << "Класс успешно удален!" << std::endl;
}

void MainMenu::addStudent() {
    // TODO: Реализовать добавление студента в классе
}

void MainMenu::removeStudent() {
    // TODO: Реализовать удаление студента из класса
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