#include "student.h"
#include <utility>

Student::Student(std::string name, int yearOfBirth)
        : name(std::move(name)), yearOfBirth(yearOfBirth) {}

std::string Student::getName() const {
    return name;
}

int Student::getYearOfBirth() const {
    return yearOfBirth;
}