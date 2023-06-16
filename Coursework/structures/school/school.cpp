#include <iostream>
#include "school.h"

School* School::instance_ = nullptr;

School::School(int school_number) {
    school_number_ = school_number;
    for (int i = 0; i < kMaxClasses; i++) {
        classes_[i] = nullptr;
    }
}

School* School::GetInstance(int school_number) {
    if (instance_ == nullptr) {
        instance_ = new School(school_number);
    }
    return instance_;
}

int School::GetSchoolNumber() const {
    return school_number_;
}

void School::AddClass(Class* class_instance) {
    auto* new_element = new StaticListElement();
    new_element->SetClass(class_instance);

    int index = 0;
    while (index < kMaxClasses && classes_[index] != nullptr) {
        index++;
    }

    if (index < kMaxClasses) {
        classes_[index] = new_element;
        if (head_ == nullptr) {
            head_ = new_element;
        }

        StaticListElement* current = head_;
        while (!current->GetNext().empty()) {
            current = classes_[index];
        }
        current->SetNext(class_instance->GetClassName());
    } else {
        std::cout << "Максимальное количество классов достигнуто." << std::endl;
    }
}

Class* School::SearchClass(const std::string& class_name) {
    for (int i = 0; i < kMaxClasses; i++) {
        if (classes_[i] != nullptr && classes_[i]->GetClass()->GetClassName() == class_name) {
            return classes_[i]->GetClass();
        }
    }
    return nullptr;
}

bool School::DeleteClass(Class* class_instance) {
    for (int i = 0; i < kMaxClasses; i++) {
        if (classes_[i] != nullptr && classes_[i]->GetClass() == class_instance) {
            delete classes_[i];
            classes_[i] = nullptr;
            return true;
        }
    }
    return false;
}

void School::ShowSchool() {
    std::cout << "\nШкола №" << school_number_ << std::endl;
    bool hasClasses = false;
    for (int i = 0; i < kMaxClasses; i++) {
        if (classes_[i] != nullptr) {
            if (!hasClasses) {
                std::cout << "Список классов:" << std::endl;
                hasClasses = true;
            }
            std::cout << " - " << classes_[i]->GetClass()->GetClassName() << std::endl;
        }
    }
    if (!hasClasses) {
        std::cout << "В школе нет классов." << std::endl;
    }
}

void School::SchoolClearMemory() {
    for (int i = 0; i < kMaxClasses; i++) {
        if (classes_[i] != nullptr) {
            delete classes_[i];
            classes_[i] = nullptr;
        }
    }
}