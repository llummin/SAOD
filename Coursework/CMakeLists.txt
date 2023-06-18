cmake_minimum_required(VERSION 3.25)
project(Coursework)

set(CMAKE_CXX_STANDARD 23)

add_executable(Coursework
        main.cpp
        structures/list/dynamic_list_element/dynamic_list_element.cpp
        structures/list/dynamic_list_element/dynamic_list_element.h
        structures/list/static_list_element/static_list_element.cpp
        structures/list/static_list_element/static_list_element.h
        structures/school/school.cpp
        structures/school/school.h
        structures/school/class/class.cpp
        structures/school/class/class.h
        structures/school/class/student/student.cpp
        structures/school/class/student/student.h
        ui/application.cpp
        ui/application.h
        data_management/data_manager.cpp
        data_management/data_manager.h
)