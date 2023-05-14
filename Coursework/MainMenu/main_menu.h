#ifndef COURSEWORK_MAIN_MENU_H
#define COURSEWORK_MAIN_MENU_H

#include "../School/school.h"

class MainMenu {
public:
    void run();

private:
    static void displayMenu();

    void processSelection(int choice);

    void addClass();

    void removeClass();

    void findClass();

    void addStudent();

    void removeStudent();

    void searchStudent();

    void saveData();

    void loadData();

    void traverseSchool();

    School school;
};

#endif //COURSEWORK_MAIN_MENU_H