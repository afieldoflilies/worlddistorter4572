cmake_minimum_required(VERSION 3.14)
project(wrlddsrt LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTORCC ON)
set (CMAKE_AUTOUIC ON)

find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(wrlddsrt main.h main.cpp qt.cpp qt.h) 
target_include_directories(wrlddsrt PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(wrlddsrt PRIVATE ${OpenCV_LIBS})
target_link_libraries(wrlddsrt PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)