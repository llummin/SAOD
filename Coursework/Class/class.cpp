#include "class.h"

Class::Class(const std::string& className) {
    this->className = className;
}

void Class::addStudent(const std::string& studentName, int yearOfBirth) {
    Student newStudent(studentName, yearOfBirth);
    students.push_back(newStudent);
}

void Class::removeStudent(int studentIndex) {
    if (studentIndex >= 0 && studentIndex < students.size()) {
        students.erase(students.begin() + studentIndex);
    }
}

Student* Class::findStudent(const std::string& studentName) {
    for (auto& student : students) {
        if (student.getName() == studentName) {
            return &student;
        }
    }
    return nullptr;
}