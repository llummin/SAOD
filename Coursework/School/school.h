#ifndef COURSEWORK_SCHOOL_H
#define COURSEWORK_SCHOOL_H

#include <vector>
#include <string>
#include "../Class/class.h"

class School {
public:
    School();

    void addClass(const std::string &className);

    void removeClass(const std::string &className);

    Class *findClass(const std::string &className);

private:
    std::vector<Class> classes;
};

#endif //COURSEWORK_SCHOOL_H