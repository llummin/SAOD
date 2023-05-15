#include "static_list_element.h"

StaticListElement::StaticListElement() {
    class_ = nullptr;
    next_ = 0;
}

void StaticListElement::SetClass(Class *class_instance) {
    class_ = class_instance;
}

Class *StaticListElement::GetClass() {
    return class_;
}

void StaticListElement::SetNext(int next) {
    next_ = next;
}

int StaticListElement::GetNext() const {
    return next_;
}