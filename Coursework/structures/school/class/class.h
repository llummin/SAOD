#ifndef COURSEWORK_CLASS_H
#define COURSEWORK_CLASS_H

#include "../../list/dynamic_list_element/dynamic_list_element.h"
#include "student/student.h"
#include <iostream>

class Class {
private:
    int class_number_;
    DynamicListElement *p_head_;

public:
    explicit Class(int class_number);

    [[nodiscard]] int GetClassNumber() const;

    bool IsEmpty();

    void AddStudent(std::string surname, int year_of_birth);

    void AddStudent(Student *student);

    Student *SearchStudent(const std::string &surname);

    bool DeleteStudent(Student *student);

    void ShowClass();

    void ListClearMemory();
};

#endif //COURSEWORK_CLASS_H
