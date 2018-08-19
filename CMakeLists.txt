cmake_minimum_required(VERSION 3.10.0)
project(nconc VERSION 0.1.0)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(nconc
        src/Hashes.cpp)

target_include_directories(nconc PUBLIC inc)
target_link_libraries(nconc ${CONAN_LIBS})

set_property(TARGET nconc PROPERTY CXX_STANDARD 17)
set_property(TARGET nconc PROPERTY CXX_STANDARD_REQUIRED ON)

enable_testing()
add_subdirectory(test)