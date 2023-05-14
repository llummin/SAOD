#ifndef COURSEWORK_SCHOOL_H
#define COURSEWORK_SCHOOL_H

#include <vector>
#include <string>
#include "../Class/class.h"

class School {
public:
    void addClass(const std::string &className);

    void removeClass(const std::string &className);

    Class *findClass(const std::string &className);

    void addStudentToClass(const std::string &className, const std::string &name, int yearOfBirth);

    void removeStudentFromClass(const std::string &className, const std::string &name);

    std::string to_string() const;

    static School from_string(const std::string &schoolStr);

private:
    std::vector<Class> classes;
};

#endif //COURSEWORK_SCHOOL_H