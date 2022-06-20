cmake_minimum_required(VERSION 3.10)

project(simple-backtrace
        LANGUAGES C
)

add_library(simple-backtrace src/backtrace.c)
target_include_directories(simple-backtrace PUBLIC include)
