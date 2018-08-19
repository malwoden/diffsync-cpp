cmake_minimum_required(VERSION 3.10.0)
project(diffsync VERSION 0.1.0)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(diffsync
        src/Hashes.cpp)

target_include_directories(diffsync PUBLIC inc)
target_link_libraries(diffsync ${CONAN_LIBS})

set_property(TARGET diffsync PROPERTY CXX_STANDARD 17)
set_property(TARGET diffsync PROPERTY CXX_STANDARD_REQUIRED ON)

enable_testing()
add_subdirectory(test)