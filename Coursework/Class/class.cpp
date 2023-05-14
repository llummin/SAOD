#include "class.h"

Class::Class(const std::string &className) {
    this->className = className;
}

std::string Class::getClassName() const {
    return className;
}

const std::vector<Student> &Class::getStudents() const {
    return students;
}

void Class::addStudent(const std::string &name, int yearOfBirth) {
    students.emplace_back(name, yearOfBirth);
}

void Class::removeStudent(const std::string &name) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->getName() == name) {
            students.erase(it);
            break;
        }
    }
}

Student *Class::findStudent(const std::string &name) {
    for (auto &student: students) {
        if (student.getName() == name) {
            return &student;
        }
    }
    return nullptr;
}

std::string Class::to_string() const {
    std::string classStr = "Class: " + className + "\n";
    for (const auto &student: students) {
        classStr += "Student: " + student.to_string() + "\n";
    }
    return classStr;
}

Class Class::from_string(const std::string &classStr) {
    std::string className;
    std::vector<Student> students;

    size_t startPos = classStr.find("Class: ") + 7;
    size_t endPos = classStr.find("\n", startPos);
    className = classStr.substr(startPos, endPos - startPos);

    size_t studentPos = classStr.find("Student: ");
    while (studentPos != std::string::npos) {
        size_t nextStudentPos = classStr.find("Student: ", studentPos + 1);
        endPos = classStr.find("\n", studentPos);
        std::string studentStr = classStr.substr(studentPos + 9, endPos - studentPos - 9);
        students.push_back(Student::from_string(studentStr));
        studentPos = nextStudentPos;
    }

    Class classObj(className);
    classObj.students = students;
    return classObj;
}
