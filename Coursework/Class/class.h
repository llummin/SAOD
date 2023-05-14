#ifndef CLASS_H
#define CLASS_H

#include <string>
#include <vector>
#include "student.h"

class Class {
public:
    Class(const std::string &className);

    void addStudent(const std::string &studentName, int yearOfBirth);

    void removeStudent(int studentIndex);

    Student *findStudent(const std::string &studentName);

private:
    std::string className;
    std::vector<Student> students;
};

#endif  // CLASS_H