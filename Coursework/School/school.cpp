#include "school.h"
#include <sstream>

void School::addClass(const std::string &className) {
    classes.emplace_back(className);
}

void School::removeClass(const std::string &className) {
    for (auto it = classes.begin(); it != classes.end(); ++it) {
        if (it->getClassName() == className) {
            classes.erase(it);
            break;
        }
    }
}

Class *School::findClass(const std::string &className) {
    for (auto &classObj: classes) {
        if (classObj.getClassName() == className) {
            return &classObj;
        }
    }
    return nullptr;
}

std::string School::to_string() const {
    std::string schoolStr;
    for (const auto &classObj: classes) {
        schoolStr += classObj.to_string();
    }
    return schoolStr;
}

School School::from_string(const std::string &schoolStr) {
    School school;
    std::istringstream iss(schoolStr);
    std::string line;

    while (std::getline(iss, line)) {
        std::string className = line;
        Class classObj(className);

        while (std::getline(iss, line) && !line.empty()) {
            std::istringstream lineStream(line);
            std::string name;
            std::string yearOfBirthStr;
            std::getline(lineStream, name, ',');
            std::getline(lineStream, yearOfBirthStr, ',');
            int yearOfBirth = std::stoi(yearOfBirthStr);
            classObj.addStudent(name, yearOfBirth);
        }

        school.addClass(className);
        Class *addedClass = school.findClass(className);
        if (addedClass) {
            *addedClass = classObj;
        }
    }

    return school;
}

