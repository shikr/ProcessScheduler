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
        util/color.cpp
        util/color.h
        util/Timer.cpp
        util/Timer.h
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
        ui/tabs/Home.cpp
        ui/tabs/Home.h
        ui/tabs/Simulator.cpp
        ui/tabs/Simulator.h
        ui/components/NumberInput.cpp
        ui/components/NumberInput.h
        ui/components/Scrollable.cpp
        ui/components/Scrollable.h
        ui/elements/memoryBar.cpp
        ui/elements/memoryBar.h
        ui/elements/processQueue.cpp
        ui/elements/processQueue.h
)

target_link_libraries(ProcessScheduler PRIVATE
        ftxui::component
        ftxui::dom
        ftxui::screen
)
