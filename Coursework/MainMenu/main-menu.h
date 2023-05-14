#ifndef MAINMENU_H
#define MAINMENU_H

#include "../School/school.h"

class MainMenu {
public:
    MainMenu();

    void startMenu();

private:
    School school;

    void displayMenu();

    void processInput(int choice);

    void addClass();

    void removeClass();

    void addStudent();

    void removeStudent();

    void searchStudent();

    void saveData();

    void loadData();
};

#endif  // MAINMENU_H