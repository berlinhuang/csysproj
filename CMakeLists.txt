cmake_minimum_required(VERSION 3.8)
project(csysproj)

set(CMAKE_C_STANDARD 99)


add_subdirectory(IPC)
add_subdirectory(thread)
add_subdirectory(concurrent)

#set(SOURCE_FILES main.c)
#add_executable(csysproj ${SOURCE_FILES})