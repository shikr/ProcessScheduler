cmake_minimum_required(VERSION 4.0)
project(ProcessScheduler)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)
FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG v6.1.9
)
FetchContent_MakeAvailable(ftxui)

add_executable(ProcessScheduler main.cpp
        base/Process.cpp
        base/Process.h
        util/random.cpp
        util/random.h
        base/Scheduler.cpp
        base/Scheduler.h
        memory/BaseMemory.cpp
        memory/BaseMemory.h
        memory/FirstMemory.cpp
        memory/FirstMemory.h
        memory/BestMemory.cpp
        memory/BestMemory.h
        memory/WorstMemory.cpp
        memory/WorstMemory.h
)

target_link_libraries(ProcessScheduler PRIVATE
        ftxui::component
        ftxui::dom
        ftxui::screen
)
