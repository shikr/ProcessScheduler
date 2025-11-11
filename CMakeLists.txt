cmake_minimum_required(VERSION 4.0)
project(ProcessScheduler)

set(CMAKE_CXX_STANDARD 23)

add_executable(ProcessScheduler main.cpp
        base/process.cpp
        base/process.h
        util/random.cpp
        util/random.h
        base/Scheduler.cpp
        base/Scheduler.h)
