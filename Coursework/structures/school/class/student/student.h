#ifndef COURSEWORK_STUDENT_H
#define COURSEWORK_STUDENT_H

#include <string>

class Student {
private:
    std::string surname_;
    int year_of_birth_;

public:
    std::string GetSurname();

    [[nodiscard]] int GetDateOfBirth() const;

    Student(std::string surname, int year_of_birth);
};

#endif //COURSEWORK_STUDENT_H
