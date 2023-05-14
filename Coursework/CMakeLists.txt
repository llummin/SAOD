cmake_minimum_required(VERSION 3.25)
project(Coursework)

set(CMAKE_CXX_STANDARD 23)

add_executable(Coursework main.cpp Student/student.cpp Student/student.h School/school.cpp School/school.h MainMenu/main_menu.cpp MainMenu/main_menu.h Class/class.cpp Class/class.h DataIO/data_io.cpp DataIO/data_io.h)
