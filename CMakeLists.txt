# CMakeLists.txt for cryptologylibrarium
cmake_minimum_required(VERSION 3.20)

# Set the project name and version
project(
    cryptolibrium
    VERSION 0.1
    DESCRIPTION "A cryptography library"
    LANGUAGES CXX
)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Add source files
file(GLOB_RECURSE SOURCES
    CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_library(
    cryptolibrium ${SOURCES}
)

# Add include directories
target_include_directories(
    cryptolibrium
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

# Add example executable
add_executable(
    caesar_example
    examples/cipher/classical/caesar_example.cpp
)

# Link the example executable with the library
target_link_libraries(
    caesar_example
    PRIVATE
        cryptolibrium
)

# Set compiler warnings
if (MSVC)
    target_compile_options(cryptolibrium PRIVATE /W4)
else()
    target_compile_options(cryptolibrium PRIVATE -Wall -Wextra -Wpedantic)
endif()


# Add tests
enable_testing()

# Add test sources
file(GLOB_RECURSE TEST_SOURCES
    CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/tests/*.cpp"
)

# Create test executables and add them to CTest
foreach(test_source ${TEST_SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)
    add_executable(${test_name} ${test_source})
    target_link_libraries(${test_name} PRIVATE cryptolibrium)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()