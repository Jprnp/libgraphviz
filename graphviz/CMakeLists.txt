cmake_minimum_required(VERSION 3.8)
project(graphviz)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES graphviz.c graphviz.h)
add_library(graphviz ${SOURCE_FILES})