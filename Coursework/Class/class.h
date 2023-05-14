#ifndef COURSEWORK_CLASS_H
#define COURSEWORK_CLASS_H

#include <string>
#include <vector>
#include "../Student/student.h"

class Class {
public:
    Class(const std::string &className);

    std::string getClassName() const;

    const std::vector<Student> &getStudents() const;

    void addStudent(const std::string &name, int yearOfBirth);

    void removeStudent(const std::string &name);

    Student *findStudent(const std::string &name);

    std::string to_string() const;

    static Class from_string(const std::string &classStr);

private:
    std::string className;
    std::vector<Student> students;
};

#endif //COURSEWORK_CLASS_H