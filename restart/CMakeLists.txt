cmake_minimum_required(VERSION 3.14)
project(wrlddsrt LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui)

add_executable(wrlddsrt main.cpp)
target_include_directories(wrlddsrt PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(wrlddsrt PRIVATE ${OpenCV_LIBS})