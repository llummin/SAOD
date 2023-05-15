#ifndef COURSEWORK_APPLICATION_H
#define COURSEWORK_APPLICATION_H

#include "../structures/school/school.h"
#include <iostream>
#include <string>

enum class Cases {
    Menu,
    AddSchool,
    AddClass,
    AddStudent,
    SearchStudent,
    DeleteClass,
    DeleteStudent,
    SearchClass,
    ClearStructure,
    ShowStructure,
    Exit
};

class Application {
private:
    School *school;

public:
    static void CaseShowMenu();

    static int GetIntInput();

    static int GetIntInputWithRange(int begin, int end);

    void Run();

    void CaseAddSchool();

    void CaseAddClass();

    void CaseAddStudent();

    void CaseDeleteClass();

    void CaseDeleteStudent();

    void CaseSearchClass();

    void CaseSearchStudent();

    void CaseClearStructure();

    void CaseShowStructure();

    void CaseExit(bool &stop);
};

#endif //COURSEWORK_APPLICATION_H