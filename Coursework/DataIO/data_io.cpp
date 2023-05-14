#include <fstream>
#include <iostream>
#include "data_io.h"

void DataIO::saveSchoolData(const School& school, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const Class& classObj : school.getClasses()) {
            file << "Class: " << classObj.getClassName() << std::endl;
            for (const Student& student : classObj.getStudents()) {
                file << "Student: " << student.getName() << ", " << student.getYearOfBirth() << std::endl;
            }
            file << std::endl;
        }
        file.close();
        std::cout << "Data saved successfully." << std::endl;
    } else {
        std::cout << "Unable to open file for saving." << std::endl;
    }
}

void DataIO::loadSchoolData(School& school, const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        school.clear();

        std::string line;
        std::string className;
        std::string studentName;
        int yearOfBirth;

        while (std::getline(file, line)) {
            if (line.find("Class: ") != std::string::npos) {
                className = line.substr(7);
                school.addClass(className);
            } else if (line.find("Student: ") != std::string::npos) {
                size_t namePos = line.find("Student: ") + 9;
                size_t commaPos = line.find(",", namePos);
                studentName = line.substr(namePos, commaPos - namePos);
                yearOfBirth = std::stoi(line.substr(commaPos + 2));
                school.addStudentToClass(className, studentName, yearOfBirth);
            }
        }

        file.close();
        std::cout << "Data loaded successfully." << std::endl;
    } else {
        std::cout << "Unable to open file for loading." << std::endl;
    }
}