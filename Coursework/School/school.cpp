#include "school.h"

School::School() {
    // TODO: Реализация конструктора
}

void School::addClass(const std::string &className) {
    Class newClass(className);
    classes.push_back(newClass);
}

void School::removeClass(int classNumber) {
    if (classNumber >= 0 && classNumber < classes.size()) {
        classes.erase(classes.begin() + classNumber);
    }
}

Class *School::findClass(int classNumber) {
    if (classNumber >= 0 && classNumber < classes.size()) {
        return &classes[classNumber];
    }
    return nullptr;
}