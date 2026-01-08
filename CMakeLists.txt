cmake_minimum_required(VERSION 3.16)
project(LeetCodeStudyGuide VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler flags
if(MSVC)
    set(CMAKE_CXX_FLAGS "/W4 /EHsc")
    set(CMAKE_CXX_FLAGS_DEBUG "/Od /Zi")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2")
else()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

# Include directories
include_directories(include)

# Source files
set(SOURCES 
    src/common.cpp
    src/data_structures/tree.cpp
    src/data_structures/heap.cpp
    src/learning_path.cpp
    src/leetcode_study_guide.cpp
    src/problem.cpp
    src/solution.cpp
)
file(GLOB_RECURSE HEADERS "include/*.h")

# Create main library
add_library(leetcode_study_guide ${SOURCES} ${HEADERS})
target_include_directories(leetcode_study_guide PUBLIC include)

# Create main executable
add_executable(main src/main.cpp)
target_link_libraries(main leetcode_study_guide)

# Create simple test executable
add_executable(simple_tests tests/simple_test.cpp)
target_link_libraries(simple_tests leetcode_study_guide)

# Enable testing
enable_testing()
add_test(NAME core_tests COMMAND simple_tests)

# Installation
install(TARGETS leetcode_study_guide main simple_tests
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin)

install(DIRECTORY include/ DESTINATION include)