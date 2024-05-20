cmake_minimum_required(VERSION 3.0)
project(gdv)

set(CMAKE_CXX_STANDARD 20)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRs})

add_executable(gdv src/main.cpp
        src/tutorials/ImgManipulation01.h
        src/tutorials/PixelManipulation02.h
        src/tutorials/VideoCam03.h
        src/tutorials/VideoFile04.h
        src/util.cpp
        src/util.h
        src/tutorials/WebcamDraw05.h
        src/tutorials/RgbToHsv06.h
        src/tutorials/ConnectedComponents07.h
        src/tutorials/TemplateMatching08.h
        src/tutorials/Blur09.h
        src/tutorials/FourierTransform10.h
        src/tutorials/Transformations11.h
        src/tutorials/AffineTransformation12.h
        src/tutorials/ProjTransformation13.h)
target_link_libraries(gdv ${OpenCV_LIBS})