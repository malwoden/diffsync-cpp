cmake_minimum_required(VERSION 3.10.0)
project(diffsync VERSION 0.1.0)

set(CMAKE_VERBOSE_MAKEFILE ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include(FindProtobuf)
find_package(Protobuf REQUIRED)
# TODO: maybe move the protbuf stuff to a sub dir as we can't customise
#       the output dir of the generated files.
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS protos/block_hash.proto)

add_library(diffsync
        src/AsyncHasher.cpp
        src/Files.cpp
        src/Hashes.cpp
        src/Protocols.cpp
        ${PROTO_SRCS})

# CMAKE_CURRENT_BINARY_DIR for the protobuf generated headers
target_include_directories(diffsync PUBLIC inc ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(diffsync
        PRIVATE ${CONAN_LIBS}
        PRIVATE $<$<CXX_COMPILER_ID:GNU>:stdc++fs>)

target_compile_options(diffsync PRIVATE -Wall -Wextra -pedantic)

target_compile_features(diffsync PUBLIC cxx_std_17)
set_property(TARGET diffsync PROPERTY CXX_EXTENSIONS OFF)

add_executable(diffsyncrunner src/main.cpp)
target_link_libraries(diffsyncrunner diffsync)

enable_testing()
add_subdirectory(test)
