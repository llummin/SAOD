#include <iostream>
#include "school.h"

int School::MaxNumberOfClasses = 11;

School::School(int school_number) {
    school_number_ = school_number;
    classes_ = new StaticListElement[MaxNumberOfClasses];
    classes_[0].SetNext(0);
    head_free_ = 1;
    for (int i = 1; i < MaxNumberOfClasses; i++) {
        classes_[i].SetNext(i == MaxNumberOfClasses - 1 ? 0 : i + 1);
    }
    class_counter_ = 0;
}

int School::GetMaxNumberOfClasses() {
    return MaxNumberOfClasses - 1;
}

Class *School::GetClass(int curr_class) {
    return classes_[curr_class].GetClass();
}

bool School::IsFull() const {
    return (class_counter_ + 1 == MaxNumberOfClasses);
}

bool School::IsEmpty() const {
    return (class_counter_ == 0);
}

int School::FindBigger(int &current, int added_class_number) {
    int parent = 0;
    current = classes_[0].GetNext();
    while (current != 0) {
        if (classes_[current].GetClass()->GetClassNumber() >= added_class_number) {
            break;
        }
        parent = current;
        current = classes_[current].GetNext();
    }
    return parent;
}

int School::SearchClass(int &curr_class, int searched_element, bool &check) {
    int prev_class = 0;
    curr_class = classes_[0].GetNext();
    while (curr_class != 0) {
        if (classes_[curr_class].GetClass()->GetClassNumber() == searched_element) {
            check = true;
            break;
        } else {
            check = false;
        }
        prev_class = curr_class;
        curr_class = classes_[curr_class].GetNext();
    }
    return prev_class;
}

bool School::SearchClass(int searched_element) {
    int curr_class = classes_[0].GetNext();
    while (curr_class != 0) {
        if (classes_[curr_class].GetClass()->GetClassNumber() == searched_element) {
            return true;
        }
        curr_class = classes_[curr_class].GetNext();
    }
    return false;
}

void School::AddClass(Class *class_instance) {
    int free_cell = head_free_;
    head_free_ = classes_[free_cell].GetNext();
    classes_[free_cell].SetClass(class_instance);
    if (IsEmpty()) {
        classes_[0].SetNext(free_cell);
        classes_[free_cell].SetNext(0);
        class_counter_++;
        return;
    }
    int curr_class = 0;
    int prev_class = FindBigger(curr_class, class_instance->GetClassNumber());
    classes_[prev_class].SetNext(free_cell);
    int pNext = curr_class == 0 ? 0 : curr_class;
    classes_[free_cell].SetNext(pNext);
    class_counter_++;
}

void School::AddClass(int class_number) {
    auto *pClass = new Class(class_number);
    AddClass(pClass);
}

void School::DeleteClass(int prev_class, int curr_class) {
    classes_[curr_class].GetClass()->ListClearMemory();
    classes_[prev_class].SetNext(classes_[curr_class].GetNext());
    classes_[curr_class].SetNext(head_free_);
    head_free_ = curr_class;
    class_counter_--;
}

void School::ShowClasses() {
    std::cout << "   Название школы: " << school_number_ << std::endl;
    if (!IsEmpty()) {
        int current = classes_[0].GetNext();
        while (current != 0) {
            classes_[current].GetClass()->ShowClass();
            current = classes_[current].GetNext();
        }
    } else {
        std::cout << "Групп для вывода нет." << std::endl;
    }
}

void School::ClearMemory() {
    int current = classes_[0].GetNext();
    while (current != 0) {
        classes_[current].GetClass()->ListClearMemory();
        current = classes_[current].GetNext();
    }
    delete[] classes_;
    classes_ = nullptr;
}