cmake_minimum_required(VERSION 3.10)
project(Filesystem)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Define source and header directories
set(SRC_DIR src)
set(INCLUDE_DIR include)
set(TEST_DIR tests)

# Define the executable for the main application
add_executable(filesystem
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/FileSystemManager.cpp
    ${SRC_DIR}/Directory.cpp
    ${SRC_DIR}/File.cpp
    ${SRC_DIR}/FileDescriptor.cpp
    ${SRC_DIR}/FileSystemObject.cpp
)

# Include directories
target_include_directories(filesystem PRIVATE ${INCLUDE_DIR})

# Define the executable for the tests
add_executable(filesystem_tests
    ${TEST_DIR}/filesystem_tests.cpp
    ${SRC_DIR}/FileSystemManager.cpp
    ${SRC_DIR}/Directory.cpp
    ${SRC_DIR}/File.cpp
    ${SRC_DIR}/FileDescriptor.cpp
    ${SRC_DIR}/FileSystemObject.cpp
)

# Include directories for tests
target_include_directories(filesystem_tests PRIVATE ${INCLUDE_DIR} ${TEST_DIR})
