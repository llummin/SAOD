#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
public:
    Student(const std::string &name, int yearOfBirth);

    std::string getName() const;

    int getYearOfBirth() const;

private:
    std::string name;
    int yearOfBirth;
};

#endif  // STUDENT_H