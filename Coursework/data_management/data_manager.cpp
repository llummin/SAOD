#include "data_manager.h"

#include <fstream>
#include <iostream>
#include <filesystem>

bool data_manager::SaveToFile(const School &school, const std::string &filename) {
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
