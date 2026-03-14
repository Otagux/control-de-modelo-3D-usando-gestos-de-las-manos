cmake_minimum_required(VERSION 3.10)

project(control_modelo_3d)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

include_directories(
    src
    ${OpenCV_INCLUDE_DIRS}
)

file(GLOB_RECURSE SOURCES
    src/*.cpp
)

add_executable(hand_control ${SOURCES})

target_link_libraries(hand_control
    ${OpenCV_LIBS}
)