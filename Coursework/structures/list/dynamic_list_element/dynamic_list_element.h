#ifndef COURSEWORK_DYNAMIC_LIST_ELEMENT_H
#define COURSEWORK_DYNAMIC_LIST_ELEMENT_H

#include "../../school/class/student/student.h"

class DynamicListElement {
private:
    Student *student_;
    DynamicListElement *next_;

public:
    DynamicListElement(Student *student, DynamicListElement *next);

    Student *GetStudent();

    DynamicListElement *GetNext();

    void SetNext(DynamicListElement *next);
};

#endif //COURSEWORK_DYNAMIC_LIST_ELEMENT_H
