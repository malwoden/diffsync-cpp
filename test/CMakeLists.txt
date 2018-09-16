# Download and unpack googletest at configure time
configure_file(Gtest.CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)

if(result)
message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)

if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

add_executable(diffsyncTests
    AsyncHasher_test.cpp
    Files_test.cpp
    Hashes_test.cpp
    Delta_test.cpp
)

target_link_libraries(diffsyncTests diffsync gtest_main)

target_compile_features(diffsyncTests PUBLIC cxx_std_17)
set_property(TARGET diffsyncTests PROPERTY CXX_EXTENSIONS OFF)

# WORKING_DIRECTORY so we can load test data relatively
add_test(
    NAME diffsyncTests
    COMMAND diffsyncTests
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)