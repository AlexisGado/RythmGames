cmake_minimum_required(VERSION 2.6)

# Define a new project
project(Exo_3)

# Find Imagine++ library
file(TO_CMAKE_PATH "$ENV{IMAGINEPP_ROOT}/CMake" p)
list(APPEND CMAKE_MODULE_PATH "${p}") #For old Imagine++
list(APPEND CMAKE_SYSTEM_FRAMEWORK_PATH /Library/Frameworks) #Mac, why not auto?
find_package(Imagine REQUIRED)

# Enable C++ 11
set(CMAKE_CXX_STANDARD 11)

# Create a new executable with the source main.cpp
add_executable(Exo_3 Exo_3.cpp)

# Link the created executable to the Imagine++ graphics library
ImagineUseModules(Exo_3 Graphics)

