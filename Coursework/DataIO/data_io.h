#ifndef COURSEWORK_DATA_IO_H
#define COURSEWORK_DATA_IO_H

#include <string>
#include "../School/school.h"

class DataIO {
public:
    static void saveSchoolData(const School& school, const std::string& filename);
    static void loadSchoolData(School& school, const std::string& filename);
};

#endif //COURSEWORK_DATA_IO_H