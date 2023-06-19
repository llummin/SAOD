#include "class.h"
#include <utility>
#include <iomanip>

Class::Class(std::string class_name) {
    class_name_ = std::move(class_name);
    p_head_ = nullptr;
}

std::string Class::GetClassName() const {
    return class_name_;
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

Student *Class::SearchStudent(const std::string &surname) {
    DynamicListElement *current = p_head_;
    while (current != nullptr) {
        if (current->GetStudent()->GetSurname() == surname) {
            return current->GetStudent();
        }
        current = current->GetNext();
    }
    return nullptr;
}

bool Class::DeleteStudent(Student *student) {
    DynamicListElement *current = p_head_;
    DynamicListElement *prev = nullptr;
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
    return false;
}


void Class::ShowClass() {
    if (!IsEmpty()) {
        std::cout << "    ├─ Ученики класса: " << std::endl;
        std::cout << "       №  | Фамилия | Год рождения" << std::endl;
        std::cout << "      ----+---------+-------------" << std::endl;
        DynamicListElement *current = p_head_;
        int student_number = 1;
        while (current != nullptr) {
            std::cout << "      " << std::setw(2) << student_number << "  | "
                      << std::left << std::setw(8) << current->GetStudent()->GetSurname()
                      << std::left << " | " << std::setw(10)
                      << current->GetStudent()->GetDateOfBirth() << std::endl;
            current = current->GetNext();
            student_number++;
        }
    } else {
        std::cout << "      Учеников для вывода нет." << std::endl;
    }
}

Class::~Class() {
    DynamicListElement *current = p_head_;
    while (current != nullptr) {
        DynamicListElement *next = current->GetNext();
        delete current;
        current = next;
        if (current != nullptr) {
            p_head_ = nullptr;
        }
    }
}
