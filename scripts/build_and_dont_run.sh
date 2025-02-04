#!/bin/bash

# Set the build directory
BUILD_DIR="build"
REPORT_DIR="build_reports"
# Check if the build directory exists
if [ -d "$BUILD_DIR" ]; then
    echo "Build directory '$BUILD_DIR' already exists."
else
    echo "Creating build directory '$BUILD_DIR'."
    mkdir "$BUILD_DIR"
fi

if [ ! -d "$BUILD_DIR/$REPORT_DIR" ]; then
    mkdir "$BUILD_DIR/$REPORT_DIR"
fi
# Check for debug mode argument
if [[ "$1" = "debug" ]]; then
    echo "Configuring for Debug mode."
#    conan install . --output-folder=build --build=missing --profile=debug -verror --format=json > $BUILD_DIR/$REPORT_DIR/conan_report.json
    cd "$BUILD_DIR" || exit
    	cmake -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug ..
else
    echo "Configuring for Release mode."
#    conan install . --output-folder=build --build=missing --profile=default -verror --format=json > $BUILD_DIR/$REPORT_DIR/conan_report.json
    cd "$BUILD_DIR" || exit
	cmake -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Release ..
fi
# Build the project using Ninja
ninja

# Extract the executable name from CMakeLists.txt
EXECUTABLE_NAME=$(grep -oP '(?<=add_executable\().*?(?=\s|\))' ../CMakeLists.txt | awk '{print $1}')

# Run the executable
#if [ -n "$EXECUTABLE_NAME" ]; then
#    echo "Running executable: ./$EXECUTABLE_NAME"
#    if [[ "$1" = "debug" ]]; then
#	shift
#	valgrind --fair-sched=yes ./$EXECUTABLE_NAME "$@"
#    else
#	./$EXECUTABLE_NAME "$@"
#    fi
#else
#    echo "No executable found in CMakeLists.txt."
#fi
