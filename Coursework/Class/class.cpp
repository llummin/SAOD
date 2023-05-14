#include "class.h"

Class::Class(const std::string &className) {
    this->className = className;
}

void Class::addStudent(const std::string &studentName, int yearOfBirth) {
    Student newStudent(studentName, yearOfBirth);
    students.push_back(newStudent);
}

void Class::removeStudent(const std::string &studentName) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->getName() == studentName) {
            students.erase(it);
            break;
        }
    }
}

Student *Class::findStudent(const std::string &studentName) {
    for (auto &student: students) {
        if (student.getName() == studentName) {
            return &student;
        }
    }
    return nullptr;
}