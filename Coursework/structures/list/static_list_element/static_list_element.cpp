#include "static_list_element.h"

#include <utility>

StaticListElement::StaticListElement() {
    class_ = nullptr;
    next_ = "";
}

void StaticListElement::SetClass(Class *class_instance) {
    class_ = class_instance;
}

Class *StaticListElement::GetClass() {
    return class_;
}

[[maybe_unused]] void StaticListElement::SetNext(std::string next) {
    next_ = std::move(next);
}

[[maybe_unused]] std::string StaticListElement::GetNext() const {
    return next_;
}

StaticListElement::~StaticListElement() {
    delete class_;
}
