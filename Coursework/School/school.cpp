#include "school.h"

void School::addClass(const std::string& className) {
    classes.emplace_back(className);
}

void School::removeClass(const std::string& className) {
    for (auto it = classes.begin(); it != classes.end(); ++it) {
        if (it->getClassName() == className) {
            classes.erase(it);
            break;
        }
    }
}

Class* School::findClass(const std::string& className) {
    for (auto& classObj : classes) {
        if (classObj.getClassName() == className) {
            return &classObj;
        }
    }
    return nullptr;
}

void School::addStudentToClass(const std::string& className, const std::string& name, int yearOfBirth) {
    Class* classObj = findClass(className);
    if (classObj) {
        classObj->addStudent(name, yearOfBirth);
    }
}

void School::removeStudentFromClass(const std::string& className, const std::string& name) {
    Class* classObj = findClass(className);
    if (classObj) {
        classObj->removeStudent(name);
    }
}

std::string School::to_string() const {
    std::string schoolStr;
    for (const auto& classObj : classes) {
        schoolStr += classObj.to_string() + "\n";
    }
    return schoolStr;
}

School School::from_string(const std::string& schoolStr) {
    School school;
    size_t classPos = schoolStr.find("Class: ");
    while (classPos != std::string::npos) {
        size_t nextClassPos = schoolStr.find("Class: ", classPos + 1);
        size_t endPos = schoolStr.find("\n", classPos);
        std::string classStr = schoolStr.substr(classPos, endPos - classPos);
        school.addClass(Class::from_string(classStr));
        classPos = nextClassPos;
    }
    return school;
}