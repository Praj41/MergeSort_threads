cmake_minimum_required(VERSION 3.16)
project(MergeSort_threads)

set(CMAKE_CXX_STANDARD 20)

add_executable(MergeSort_threads main.cpp RNG.h Timer.h)