cmake_minimum_required(VERSION 3.12)

project(week1)

set(CMAKE_CXX_STANDARD 20)

set(TARGETS 1_factorial 2_fibonacci 3_binary_search 4_permutations 5_lcs 6_power_set)

foreach(target ${TARGETS})
    add_executable(${target} ${target}.cpp)
endforeach()