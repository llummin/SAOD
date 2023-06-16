#ifndef COURSEWORK_SCHOOL_H
#define COURSEWORK_SCHOOL_H

#include "../list/static_list_element/static_list_element.h"
#include <string>

const int kMaxClasses = 10;

class School {
private:
    static School *instance_;
    int school_number_;
    StaticListElement *head_{};
    StaticListElement *classes_[kMaxClasses]{};

public:
    static School *GetInstance(int school_number);

    [[nodiscard]] int GetSchoolNumber() const;

    void AddClass(Class *class_instance);

    Class *SearchClass(const std::string &class_name);

    bool DeleteClass(Class *class_instance);

    void SchoolClearMemory();

    explicit School(int school_number);

    void ShowSchoolStructure();
};

#endif //COURSEWORK_SCHOOL_H
