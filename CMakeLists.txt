cmake_minimum_required(VERSION 3.10)
project(PoorMansVector)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(tests tests/test_vector.cpp)
target_link_libraries(tests PRIVATE vector Catch2::Catch2WithMain)

add_library(vector src/vector.cpp)
target_include_directories(vector PUBLIC include)

add_executable(main main.cpp)
target_link_libraries(main vector)