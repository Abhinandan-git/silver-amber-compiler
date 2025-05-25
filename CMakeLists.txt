cmake_minimum_required(VERSION 3.13)  # Minimum required version of CMake
project(sacompiler CXX)             # Enable both C and C++ support

# Set C++ and C standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add main.cpp from ./src/
set(SOURCE_FILES ./src/main.cpp)

# Define the executable
add_executable(sacompiler ${SOURCE_FILES})
