#include "student.h"

std::string Student::GetSurname() {
    return surname_;
}

int Student::GetDateOfBirth() const {
    return year_of_birth_;
}

Student::Student(std::string surname, int year_of_birth) {
    surname_ = std::move(surname);
    year_of_birth_ = year_of_birth;
}