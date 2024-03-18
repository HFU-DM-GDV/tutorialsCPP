cmake_minimum_required(VERSION 3.27)
project(gdv)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRs})

add_executable(gdv src/main.cpp
        src/ImgManipulation01.h)
target_link_libraries(gdv ${OpenCV_LIBS})