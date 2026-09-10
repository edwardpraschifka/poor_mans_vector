cmake_minimum_required(VERSION 3.10)
project(PoorMansVector)
set(CMAKE_CXX_STANDARD 17)

add_library(vector src/vector.cpp)
target_include_directories(vector PUBLIC include)

add_executable(main main.cpp)
target_link_libraries(main vector)