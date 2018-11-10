cmake_minimum_required(VERSION 3.12)
project(RotationIntersectionOfCube)

set(CMAKE_CXX_STANDARD 11)

set(Sources gwindow.cpp DrawInterWindow.cpp main.cpp R2Graph.cpp R3Graph.cpp Rotation.cpp)
set(Headers gwindow.h DrawInterWindow.h R2Graph.h R3Graph.h Rotation.h)

add_executable(superlib ${Sources} ${Headers})

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})
target_link_libraries(superlib ${X11_LIBRARIES})