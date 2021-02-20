cmake_minimum_required(VERSION 3.17)

project(ML_CPP)

set(CMAKE_CXX_STANDARD 11)

#add_executable(ML_CPP main.cpp Matrix/Matrix.h Matrix/Matrix.cpp
#        ANN/ann.cpp ANN/ann.h Matrix/matrixtest.cpp CV_Basic/loadImage.cpp
#        CV_Basic/randomGenerator.cpp)
add_executable(ML_CPP main.cpp)

set(OpenCV_DIR)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(ML_CPP ${OpenCV_LIBS})

