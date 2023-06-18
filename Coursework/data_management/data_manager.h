#ifndef COURSEWORK_DATA_MANAGER_H
#define COURSEWORK_DATA_MANAGER_H

#include "../structures/school/school.h"

class data_manager {
public:
    static bool SaveToFile(const School &school, const std::string &filename);
};


#endif //COURSEWORK_DATA_MANAGER_H
