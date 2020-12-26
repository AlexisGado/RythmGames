cmake_minimum_required(VERSION 2.9)

# Define a new project
project(atel_prog)

 list(APPEND CMAKE_PREFIX_PATH "/usr/local/Qt-5.15.2")

# Find Imagine++ library
file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}/CMake" p)
list(APPEND CMAKE_MODULE_PATH "${p}") #For old Imagine++
list(APPEND CMAKE_SYSTEM_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?
find_package(Imagine REQUIRED)

# Enable C++ 11
set(CMAKE_CXX_STANDARD 11)

# Create a new executable with the source main.cpp
add_executable(atel_prog main.cpp stack.cpp stack2.cpp stack2.h stack.h piano_tiles.cpp piano_tiles.h piano_tiles_course.cpp piano_tiles_course.h general.cpp general.h)
# Link the created executable to the Imagine++ graphics library
ImagineUseModules(atel_prog Graphics)

