#ifndef COURSEWORK_STATIC_LIST_ELEMENT_H
#define COURSEWORK_STATIC_LIST_ELEMENT_H

#include "../../school/class/class.h"

class StaticListElement {
private:
    Class *class_;
    std::string next_;

public:
    StaticListElement();

    void SetClass(Class *class_instance);

    Class *GetClass();

    [[maybe_unused]] void SetNext(std::string next);

    [[maybe_unused]] [[nodiscard]] std::string GetNext() const;
};

#endif //COURSEWORK_STATIC_LIST_ELEMENT_H
