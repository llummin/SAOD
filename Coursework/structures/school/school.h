#ifndef COURSEWORK_SCHOOL_H
#define COURSEWORK_SCHOOL_H

#include "../list/static_list_element/static_list_element.h"
#include <string>
#include <list>

const int kMaxClasses = 5;

class School {
private:
    int school_number_;
    std::list<StaticListElement *> classes_;

public:
    School() : school_number_(0) {}

    explicit School(int school_number);

    [[nodiscard]] int GetSchoolNumber() const;

    void SetSchoolNumber(int school_number);

    friend class data_manager;

    void AddClass(Class *class_instance);

    Class *SearchClass(const std::string &class_name);

    bool DeleteClass(Class *class_instance);

    void SchoolClearMemory();

    void ShowSchoolStructure();
};

#endif // COURSEWORK_SCHOOL_H
