cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MPU6050Test)

# Add the executable
add_executable(MPU6050Test MPU6050_test_main.cpp MPU6050_test.cpp)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Link the pigpio library
find_library(PIGPIO_LIBRARY pigpio)
if (NOT PIGPIO_LIBRARY)
    message(FATAL_ERROR "pigpio library not found")
endif()
target_link_libraries(MPU6050Test ${PIGPIO_LIBRARY})
