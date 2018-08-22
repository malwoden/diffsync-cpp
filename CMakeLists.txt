cmake_minimum_required(VERSION 3.10.0)
project(diffsync VERSION 0.1.0)

set(CMAKE_VERBOSE_MAKEFILE ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(diffsync
        src/AsyncHasher.cpp
        src/Files.cpp
        src/Hashes.cpp)

target_include_directories(diffsync PUBLIC inc)

target_link_libraries(diffsync
        PRIVATE ${CONAN_LIBS}
        PRIVATE $<$<CXX_COMPILER_ID:GNU>:stdc++fs>)

target_compile_options(diffsync PRIVATE -Wall -Wextra -pedantic)

target_compile_features(diffsync PUBLIC cxx_std_17)
set_property(TARGET diffsync PROPERTY CXX_EXTENSIONS OFF)

enable_testing()
add_subdirectory(test)
