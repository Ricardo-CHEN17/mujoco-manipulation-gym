cmake_minimum_required(VERSION 3.22)

# Define the project name, version and name
project(mujoco_manipulation_gym VERSION 0.1.0 LANGUAGES CXX)

# Set morden C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# The default compilation mode is Release, with aggressive optimizations enabled
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Highest level optimization; Removes the extra runtime overhead of assert
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Search for the C++ core dependency libraries installed in the Pixi environment
find_package(Eigen3 REQUIRED NO_MODULE)
find_package(pinocchio REQUIRED)
find_package(spdlog REQUIRED)
find_package(Catch2 3 REQUIRED)

message(STATUS ">>> [mmgym] Eigen3 version ${Eigen3_VERSION}")
message(STATUS ">>> [mmgym] pinocchio version ${pinocchio_VERSION}")

enable_testing()

# Recursively introduce sub-build modules
add_subdirectory(core)
add_subdirectory(tests/cpp)