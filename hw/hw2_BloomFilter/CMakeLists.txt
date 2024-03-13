cmake_minimum_required(VERSION 3.27)
project(hw2_BloomFilter)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(hw2_BloomFilter
        main.cpp
        MurmurHash3.h)
