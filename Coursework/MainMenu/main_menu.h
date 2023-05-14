#ifndef COURSEWORK_MAIN_MENU_H
#define COURSEWORK_MAIN_MENU_H

#include "../School/school.h"
#include "../DataIO/data_io.h"

class MainMenu {
public:
    void run();

private:
    School school;

    void displayMenu();

    void processSelection(int choice);

    void addClass();

    void removeClass();

    void addStudent();

    void removeStudent();

    void searchStudent();

    void saveData();

    void loadData();
};

#endif //COURSEWORK_MAIN_MENU_H