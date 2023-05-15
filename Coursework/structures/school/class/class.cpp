#include "class.h"
#include <utility>
#include <iomanip>

Class::Class(int class_number) {
    class_number_ = class_number;
    p_head_ = nullptr;
}

int Class::GetClassNumber() const {
    return class_number_;
}

bool Class::IsEmpty() {
    return (p_head_ == nullptr);
}

void Class::AddStudent(std::string surname, int year_of_birth) {
    auto *student = new Student(std::move(surname), year_of_birth);
    AddStudent(student);
}

void Class::AddStudent(Student *student) {
    auto *list_element = new DynamicListElement(student, p_head_);
    p_head_ = list_element;
}

Student* Class::SearchStudent(const std::string& surname) {
    DynamicListElement* current = p_head_;
    while (current != nullptr) {
        if (current->GetStudent()->GetSurname() == surname) {
            return current->GetStudent();
        }
        current = current->GetNext();
    }
    return nullptr;
}

bool Class::DeleteStudent(Student* student) {
    if (!IsEmpty()) {
        DynamicListElement* current = p_head_;
        DynamicListElement* prev = nullptr;
        while (current != nullptr) {
            if (current->GetStudent() == student) {
                if (prev != nullptr) {
                    prev->SetNext(current->GetNext());
                } else {
                    p_head_ = current->GetNext();
                }
                delete current;
                return true;
            }
            prev = current;
            current = current->GetNext();
        }
    }
    return false;
}


void Class::ShowClass() {
    std::cout << "\n\tКласс " << class_number_ << std::endl;
    if (!IsEmpty()) {
        std::cout << "  №  |    Фамилия    | Год рождения" << std::endl;
        std::cout << "-----+--------------+-------------" << std::endl;
        DynamicListElement *current = p_head_;
        int student_number = 1;
        while (current != nullptr) {
            std::cout << std::setw(4) << student_number << "  | " << std::setw(13) << current->GetStudent()->GetSurname()
                      << " | " << std::setw(5) << current->GetStudent()->GetDateOfBirth() << std::endl;
            current = current->GetNext();
            student_number++;
        }
    } else {
        std::cout << "Учеников для вывода нет." << std::endl;
    }
}


void Class::ListClearMemory() {
    DynamicListElement *current = p_head_;
    DynamicListElement *temp;
    while (current != nullptr) {
        temp = current->GetNext();
        delete current;
        current = temp;
    }
    p_head_ = nullptr;
}