cmake_minimum_required(VERSION 3.20)
project(MachineControlSimulator)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

add_executable(MachineControlSimulator
        src/main.cpp
        src/models/SensorEvent.h
)
target_link_libraries(MachineControlSimulator PRIVATE Threads::Threads)
