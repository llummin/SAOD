#ifndef COURSEWORK_CLASS_H
#define COURSEWORK_CLASS_H

#include "../../list/dynamic_list_element/dynamic_list_element.h"
#include "student/student.h"
#include <iostream>

class Class {
private:
    std::string class_name_;
    DynamicListElement *p_head_;

public:
    explicit Class(std::string class_name);

    [[nodiscard]] std::string GetClassName() const;

    bool IsEmpty();

    void AddStudent(std::string surname, int year_of_birth);

    void AddStudent(Student *student);

    Student *SearchStudent(const std::string &surname);

    bool DeleteStudent(Student *student);

    void ShowClass();

    void ListClearMemory();
};

#endif //COURSEWORK_CLASS_H
