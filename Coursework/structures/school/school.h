#ifndef COURSEWORK_SCHOOL_H
#define COURSEWORK_SCHOOL_H

#include "../list/static_list_element/static_list_element.h"
#include <string>

class School {
private:
    std::string school_name_;
    static int MaxNumberOfClasses;
    int class_counter_;
    int head_free_;
    StaticListElement *classes_;

public:
    explicit School(std::string school_name);

    static int GetMaxNumberOfClasses();

    Class *GetClass(int curr_class);

    [[nodiscard]] bool IsFull() const;

    [[nodiscard]] bool IsEmpty() const;

    int FindBigger(int &current, int added_class_number);

    int SearchClass(int &curr_class, int searched_element, bool &check);

    bool SearchClass(int searched_element);

    void AddClass(Class *class_instance);

    void AddClass(int class_number);

    void DeleteClass(int prev_class, int curr_class);

    void ShowClasses();

    void ClearMemory();
};

#endif //COURSEWORK_SCHOOL_H