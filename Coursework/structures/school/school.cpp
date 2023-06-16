#include <iostream>
#include "school.h"

School* School::instance_ = nullptr;

School::School(int school_number) {
    school_number_ = school_number;
    for (auto & classes : classes_) {
        classes = nullptr;
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
    for (auto & classes : classes_) {
        if (classes != nullptr && classes->GetClass()->GetClassName() == class_name) {
            return classes->GetClass();
        }
    }
    return nullptr;
}

bool School::DeleteClass(Class* class_instance) {
    for (auto & classes : classes_) {
        if (classes != nullptr && classes->GetClass() == class_instance) {
            delete classes;
            classes = nullptr;
            return true;
        }
    }
    return false;
}

void School::ShowSchool() {
    std::cout << "\nШкола №" << school_number_ << std::endl;
    bool hasClasses = false;
    for (auto & classes : classes_) {
        if (classes != nullptr) {
            if (!hasClasses) {
                std::cout << "Список классов:" << std::endl;
                hasClasses = true;
            }
            std::cout << " - " << classes->GetClass()->GetClassName() << std::endl;
        }
    }
    if (!hasClasses) {
        std::cout << "В школе нет классов." << std::endl;
    }
}

void School::SchoolClearMemory() {
    for (auto & classes : classes_) {
        if (classes != nullptr) {
            delete classes;
            classes = nullptr;
        }
    }
}