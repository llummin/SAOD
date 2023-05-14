#include <sstream>
#include <utility>
#include "class.h"

Class::Class(std::string className)
        : className(std::move(className)) {}

std::string Class::getClassName() const {
    return className;
}

void Class::addStudent(const std::string &name, int yearOfBirth) {
    students.emplace_back(name, yearOfBirth);
}

void Class::removeStudent(const std::string &name) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->getName() == name) {
            students.erase(it);
            break;
        }
    }
}

Student *Class::findStudent(const std::string &name) {
    for (auto &student: students) {
        if (student.getName() == name) {
            return &student;
        }
    }
    return nullptr;
}

std::string Class::to_string() const {
    std::string classStr = className + "\n";
    for (const auto &student: students) {
        classStr += student.getName() + "," + std::to_string(student.getYearOfBirth()) + "\n";
    }
    return classStr;
}

Class Class::from_string(const std::string &classStr) {
    std::istringstream iss(classStr);
    std::string line;
    std::getline(iss, line);
    Class newClass(line);

    while (std::getline(iss, line)) {
        std::istringstream lineStream(line);
        std::string name;
        std::string yearOfBirthStr;
        std::getline(lineStream, name, ',');
        std::getline(lineStream, yearOfBirthStr, ',');
        int yearOfBirth = std::stoi(yearOfBirthStr);
        newClass.addStudent(name, yearOfBirth);
    }

    return newClass;
}