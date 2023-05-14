#ifndef SCHOOL_H
#define SCHOOL_H

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

#endif  // SCHOOL_H