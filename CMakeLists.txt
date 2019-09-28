cmake_minimum_required(VERSION 3.12.1) #CMake version check
project(AppSec-Assignment1) #Project Name
set(CMAKE_CXX_STANDARD 14) #Enable c++14 standard

set(SOURCE_FILES main.c)

add_executable(AppSec-Assignment1 ${SOURCE_FILES})
add_executable(AppSec-Assignment1-Test test_main.c)

target_link_libraries(AppSec-Assignment1-Test libcheck)