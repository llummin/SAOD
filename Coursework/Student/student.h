#ifndef COURSEWORK_STUDENT_H
#define COURSEWORK_STUDENT_H

#include <string>

class Student {
public:
    Student(std::string name, int yearOfBirth);

    [[nodiscard]] std::string getName() const;

    [[nodiscard]] int getYearOfBirth() const;

private:
    std::string name;
    int yearOfBirth;
};

#endif //COURSEWORK_STUDENT_H