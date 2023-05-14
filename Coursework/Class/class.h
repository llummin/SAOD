#ifndef COURSEWORK_CLASS_H
#define COURSEWORK_CLASS_H

#include <string>
#include <vector>
#include "../Student/student.h"

class Class {
public:
    explicit Class(std::string className);

    [[nodiscard]] std::string getClassName() const;

    void addStudent(const std::string &name, int yearOfBirth);

    void removeStudent(const std::string &name);

    Student *findStudent(const std::string &name);

    [[nodiscard]] std::string to_string() const;

    static Class from_string(const std::string &classStr);

private:
    std::string className;
    std::vector<Student> students;
};

#endif //COURSEWORK_CLASS_H