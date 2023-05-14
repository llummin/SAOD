#include "school.h"

School::School() {
    // TODO: Реализация конструктора
}

void School::addClass(const std::string& className) {
    Class newClass(className);
    classes.push_back(newClass);
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