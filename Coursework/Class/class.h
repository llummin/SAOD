#ifndef COURSEWORK_CLASS_H
#define COURSEWORK_CLASS_H

#include <string>
#include <vector>
#include "../Student/student.h"

class Class {
public:
    Class(const std::string &className);

    void addStudent(const std::string &studentName, int yearOfBirth);

    void removeStudent(const std::string &studentName);

    Student *findStudent(const std::string &studentName);

private:
    std::string className;
    std::vector<Student> students;
};

#endif //COURSEWORK_CLASS_H