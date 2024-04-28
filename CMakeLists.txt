cmake_minimum_required(VERSION 3.10)
project(SQL)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(SQL
        main.cpp
        Database.cpp
        Table.cpp
)
