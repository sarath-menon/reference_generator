cmake_minimum_required(VERSION 3.16)
project(reference_generator VERSION 0.1)
set(CMAKE_CXX_STANDARD 17)

include_directories(external/helper)

# Find requirements
find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)
find_package(MAVSDK REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)

add_subdirectory(lib)
add_subdirectory(apps)
add_subdirectory(tests)

