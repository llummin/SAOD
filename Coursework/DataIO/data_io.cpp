#include <fstream>
#include <iostream>
#include "data_io.h"

void DataIO::saveSchoolData(const School &school, const std::string &filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << school.to_string();
        file.close();
        std::cout << "Данные успешно сохранены." << std::endl;
    } else {
        std::cout << "Не удалось открыть файл!" << std::endl;
    }
}

void DataIO::loadSchoolData(School &school, const std::string &filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string schoolStr((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        school = School::from_string(schoolStr);
        file.close();
        std::cout << "Данные успешно сохранены." << std::endl;
    } else {
        std::cout << "Не удалось открыть файл!" << std::endl;
    }
}