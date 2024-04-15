cmake_minimum_required(VERSION 3.10)

# Set the project name
project(ADS1115WrapperTest)

# Add the executable
add_executable(ADS1115WrapperTest C25A_Wrapper.cpp ADS1115_Wrapper.cpp)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
