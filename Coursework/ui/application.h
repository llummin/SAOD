#ifndef COURSEWORK_APPLICATION_H
#define COURSEWORK_APPLICATION_H

#include "../structures/school/school.h"
#include <iostream>
#include <string>

enum class Cases {
    Menu,
    AddSchool,
    AddClass,
    SearchClass,
    DeleteClass,
    AddStudent,
    SearchStudent,
    DeleteStudent,
    ClearStructure,
    ShowStructure,
    Exit
};

class Application {
private:
    School *school;

public:
    static void ShowMenu();

    static int GetIntInput();

    static int GetIntInputWithRange(int begin, int end);

    void Run();

    void AddSchool();

    void AddClass();

    void AddStudent();

    void DeleteClass();

    void DeleteStudent();

    void SearchClass();

    void SearchStudent();

    void ClearStructure();

    void ShowStructure();

    static void Exit(bool &stop);
};

#endif //COURSEWORK_APPLICATION_H