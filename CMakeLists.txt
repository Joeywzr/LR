cmake_minimum_required(VERSION 3.9)
project(LR)

set(CMAKE_CXX_STANDARD 11)

add_executable(LR main.cpp LR_grammer.cpp LR_grammer.h)