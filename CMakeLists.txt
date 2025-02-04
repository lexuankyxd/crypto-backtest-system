cmake_minimum_required(VERSION 3.24)

project(main)

include(FetchContent)
# Find packages
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

FetchContent_Declare(matplotplusplus
        GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus
        GIT_TAG origin/master) # or whatever tag you want
FetchContent_MakeAvailable(matplotplusplus)


# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Adding all files into 1 source var
file(GLOB SOURCES source/alpha/*.cpp)
file(GLOB S1 source/utils/*.cpp)

list(APPEND SOURCES ${S1})

# Set flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pg -fprofile-arcs -ftest-coverage")
endif()

# Define the executable target
add_executable(main source/main.cpp ${SOURCES})

# Link the nlohmann_json library to the 'main' target
target_link_libraries(main nlohmann_json::nlohmann_json matplot)
