#include <iostream>
#include "school.h"

School::School(int school_number) : school_number_(school_number), class_count(0) {
    for (auto &classe: classes_) {
        classe = nullptr;
    }
}

int School::GetSchoolNumber() const {
    return school_number_;
}

void School::SetSchoolNumber(int school_number) {
    school_number_ = school_number;
}

void School::AddClass(Class *class_instance) {
    if (class_count >= kMaxClasses) {
        std::cout << "Максимальное количество классов достигнуто!" << std::endl;
        return;
    }

    if (SearchClass(class_instance->GetClassName()) != nullptr) {
        std::cout << "Класс '" << class_instance->GetClassName() << "' уже существует в школе!" << std::endl;
        return;
    }

    auto *new_element = new StaticListElement();
    new_element->SetClass(class_instance);

    classes_[class_count] = new_element;
    class_count++;

    std::cout << "Класс '" << class_instance->GetClassName() << "' успешно добавлен в школу!" << std::endl;
}

Class *School::SearchClass(const std::string &class_name) {
    for (int i = 0; i < class_count; i++) {
        if (classes_[i] != nullptr && classes_[i]->GetClass()->GetClassName() == class_name) {
            return classes_[i]->GetClass();
        }
    }
    return nullptr;
}

bool School::DeleteClass(Class *class_instance) {
    for (int i = 0; i < class_count; i++) {
        if (classes_[i] != nullptr && classes_[i]->GetClass() == class_instance) {
            delete classes_[i];
            classes_[i] = nullptr;
            for (int j = i; j < class_count - 1; j++) {
                classes_[j] = classes_[j + 1];
            }
            classes_[class_count - 1] = nullptr;
            class_count--;
            return true;
        }
    }
    return false;
}

void School::ShowSchoolStructure() {
    std::cout << "\nШкола №" << school_number_ << std::endl;

    for (int i = 0; i < class_count; i++) {
        Class *currentClass = classes_[i]->GetClass();
        std::cout << "  └─ Класс: " << currentClass->GetClassName() << std::endl;
        currentClass->ShowClass();
    }
}

void School::SchoolClearMemory() {
    for (int i = 0; i < class_count; i++) {
        delete classes_[i];
        classes_[i] = nullptr;
    }
    class_count = 0;
}

School::~School() {
    for (int i = 0; i < class_count; i++) {
        delete classes_[i];
        classes_[i] = nullptr;
    }
}
