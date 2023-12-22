cmake_minimum_required(VERSION 3.24)

project(AdventOfCode2023)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "\
${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Wpedantic \
-fsanitize=address \
")

add_subdirectory(googletest)

add_subdirectory(day1)
add_subdirectory(day2)
add_subdirectory(day3)
add_subdirectory(day4)
add_subdirectory(day5)
add_subdirectory(day6)
add_subdirectory(day7)
