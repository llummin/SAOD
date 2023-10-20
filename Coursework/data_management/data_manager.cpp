#include "data_manager.h"

#include <fstream>
#include <iostream>
#include <filesystem>

bool DataManager::SaveToFile(const School &school, const std::string &filename) {
    std::string fullFilePath = "C:/Users/maxim/Documents/SAOD/Coursework/" + filename;

    std::ofstream outFile(fullFilePath, std::ios::trunc);
    if (!outFile.is_open()) {
        return false;
    }

    outFile << school.GetSchoolNumber() << std::endl;
    for (auto &classes: school.classes_) {
        outFile << classes->GetClass()->GetClassName() << std::endl;
        DynamicListElement *current = classes->GetClass()->p_head_;
        while (current != nullptr) {
            outFile << current->GetStudent()->GetSurname() << " " << current->GetStudent()->GetDateOfBirth()
                    << std::endl;
            current = current->GetNext();
        }
    }

    outFile.close();
    return true;
}

bool DataManager::LoadFromFile(School *&school, const std::string &filename) {
    std::string fullFilePath = "C:/Users/maxim/Documents/SAOD/Coursework/" + filename;

    std::ifstream inFile(fullFilePath);
    if (!inFile.is_open()) {
        return false;
    }

    int schoolNumber;
    if (!(inFile >> schoolNumber)) {
        inFile.close();
        return false;
    }

    if (school == nullptr) {
        school = new School(schoolNumber);
    } else {
        school->SetSchoolNumber(schoolNumber);
    }

    std::string line;
    std::string className;

    while (std::getline(inFile, line)) {
        if (line.empty()) {
            continue;
        }

        if (line.find(' ') != std::string::npos) {
            std::istringstream iss(line);
            std::string surname;
            int yearOfBirth;
            iss >> surname >> yearOfBirth;

            Class *classInstance = school->SearchClass(className);
            if (classInstance == nullptr) {
                classInstance = new Class(className);
                school->AddClass(classInstance);
            }
            classInstance->AddStudent(surname, yearOfBirth);
        } else {
            className = line;
            auto *classInstance = new Class(className);
            school->AddClass(classInstance);
        }
    }

    inFile.close();
    return true;
}
