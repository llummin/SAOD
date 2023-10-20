#include <iostream>
#include "school.h"

School::School(int school_number) : school_number_(school_number) {

}

int School::GetSchoolNumber() const {
    return school_number_;
}

void School::SetSchoolNumber(int school_number) {
    school_number_ = school_number;
}

void School::AddClass(Class *class_instance) {
    if (classes_.size() >= kMaxClasses) {
        std::cout << "Максимальное количество классов достигнуто!" << std::endl;
        return;
    }

    if (SearchClass(class_instance->GetClassName()) != nullptr) {
        std::cout << "Класс '" << class_instance->GetClassName() << "' уже существует в школе!" << std::endl;
        return;
    }

    auto *new_element = new StaticListElement();
    new_element->SetClass(class_instance);

    classes_.push_back(new_element);
    classes_.sort([](StaticListElement *a, StaticListElement *b) {
        return a->GetClass()->GetClassName() < b->GetClass()->GetClassName();
    });

    std::cout << "Класс '" << class_instance->GetClassName() << "' успешно добавлен в школу!" << std::endl;
}


Class *School::SearchClass(const std::string &class_name) {
    for (auto &classes: classes_) {
        if (classes != nullptr && classes->GetClass()->GetClassName() == class_name) {
            return classes->GetClass();
        }
    }
    return nullptr;
}

bool School::DeleteClass(Class *class_instance) {
    classes_.remove_if([class_instance](StaticListElement *element) {
        return element->GetClass() == class_instance;
    });
    return true;
}

void School::ShowSchoolStructure() {
    std::cout << "\nШкола №" << school_number_ << std::endl;

    for (auto &classes: classes_) {
        Class *currentClass = classes->GetClass();
        std::cout << "  └─ Класс: " << currentClass->GetClassName() << std::endl;
        currentClass->ShowClass();
    }
}

void School::SchoolClearMemory() {
    for (auto &classes: classes_) {
        delete classes;
    }
    classes_.clear();
}
