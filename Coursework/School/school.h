#ifndef SCHOOL_H
#define SCHOOL_H

#include <vector>
#include <string>

class School {
public:
    School();

    void addClass(const std::string &className);

    void removeClass(int classNumber);

    Class *findClass(int classNumber);

private:
    std::vector<Class> classes;
};

#endif  // SCHOOL_H