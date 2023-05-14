#include "student.h"

Student::Student(const std::string &name, int yearOfBirth) {
    this->name = name;
    this->yearOfBirth = yearOfBirth;
}

std::string Student::getName() const {
    return name;
}

int Student::getYearOfBirth() const {
    return yearOfBirth;
}