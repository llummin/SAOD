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

std::string Student::to_string() const {
    return name + "," + std::to_string(yearOfBirth);
}

Student Student::from_string(const std::string &studentStr) {
    size_t commaPos = studentStr.find(",");
    std::string name = studentStr.substr(0, commaPos);
    int yearOfBirth = std::stoi(studentStr.substr(commaPos + 1));
    return Student(name, yearOfBirth);
}