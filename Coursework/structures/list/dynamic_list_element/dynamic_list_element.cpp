#include "dynamic_list_element.h"

DynamicListElement::DynamicListElement(Student *student, DynamicListElement *next) {
    student_ = student;
    next_ = next;
}

Student *DynamicListElement::GetStudent() {
    return student_;
}

DynamicListElement *DynamicListElement::GetNext() {
    return next_;
}

void DynamicListElement::SetNext(DynamicListElement *next) {
    next_ = next;
}
