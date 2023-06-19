#ifndef COURSEWORK_STATIC_LIST_ELEMENT_H
#define COURSEWORK_STATIC_LIST_ELEMENT_H

#include "../../school/class/class.h"

class StaticListElement {
private:
    Class *class_;
    std::string next_;

public:
    StaticListElement();

    ~StaticListElement();

    void SetClass(Class *class_instance);

    Class *GetClass();

    void SetNext(std::string next);

    std::string GetNext() const;
};

#endif //COURSEWORK_STATIC_LIST_ELEMENT_H
