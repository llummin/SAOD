#ifndef COURSEWORK_STATIC_LIST_ELEMENT_H
#define COURSEWORK_STATIC_LIST_ELEMENT_H

#include "../../school/class/class.h"

class StaticListElement {
private:
    Class *class_;
    int next_;

public:
    StaticListElement();

    void SetClass(Class *class_instance);

    Class *GetClass();

    void SetNext(int next);

    [[nodiscard]] int GetNext() const;
};

#endif //COURSEWORK_STATIC_LIST_ELEMENT_H