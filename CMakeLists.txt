cmake_minimum_required(VERSION 2.8)

project(median CXX)

set(CMAKE_CXX_STANDARD 11) # This is equal to QMAKE_CXX_FLAGS += -std=c++0x
set(CMAKE_CXX_FLAGS "-std=c++0x")


# EasyBMP Library
include_directories(./src/EasyBMP)
aux_source_directory(./src/EasyBMP EASYBMP_SOURCES)
add_library(easybmp STATIC ${EASYBMP_SOURCES})


# own Median implementation
include_directories(./src)
aux_source_directory(./src MEDIAN_SOURCES)
add_executable(${PROJECT_NAME} ${MEDIAN_SOURCES})

target_link_libraries(${PROJECT_NAME} easybmp)
