cmake_minimum_required(VERSION 3.10)

# Set the project name
project(ADS1115WrapperTest)

# Add the executable
add_executable(ADS1115WrapperTest C25A_ADS1115_Pressure_test.cpp ADS1115.cpp)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_library(PIGPIO_LIBRARY pigpio)
if (NOT PIGPIO_LIBRARY)
    message(FATAL_ERROR "pigpio library not found")
endif()
target_link_libraries(MPU6050Test ${PIGPIO_LIBRARY})
