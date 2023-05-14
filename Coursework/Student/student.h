#ifndef COURSEWORK_STUDENT_H
#define COURSEWORK_STUDENT_H

#include <string>

class Student {
public:
    Student(const std::string &name, int yearOfBirth);

    std::string getName() const;

    int getYearOfBirth() const;

    std::string to_string() const;

    static Student from_string(const std::string &studentStr);

private:
    std::string name;
    int yearOfBirth;
};

#endif //COURSEWORK_STUDENT_H