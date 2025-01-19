cmake_minimum_required(VERSION 3.15)

project(main)

# Find the nlohmann_json package
find_package(nlohmann_json REQUIRED)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Adding all files into 1 source var
file(GLOB SOURCES source/alpha/*.cpp)
file(GLOB S1 source/utils/*.cpp)

list(APPEND SOURCES ${S1})

# Define the executable target
add_executable(main source/main.cpp ${SOURCES})

# Link the nlohmann_json library to the 'main' target
target_link_libraries(main nlohmann_json::nlohmann_json)
