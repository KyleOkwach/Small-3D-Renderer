cmake_minimum_required(VERSION 3.0)

project(Rebel3D)

# Create the build directory
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Add a target to compile main.cpp
add_executable(Rebel3D ${CMAKE_SOURCE_DIR}/main.cpp)

# Specify libraries to link against
target_link_libraries(Rebel3D comdlg32 gdi32)