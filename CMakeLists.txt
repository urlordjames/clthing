cmake_minimum_required(VERSION "3.7")

project("clthing")

# include OpenCL
find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIRS})
link_directories(${OpenCL_LIBRARY})

add_executable(${PROJECT_NAME} src/main.cpp)

# link OpenCL
target_link_libraries(${PROJECT_NAME} ${OpenCL_LIBRARY})
