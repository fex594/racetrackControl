cmake_minimum_required(VERSION 2.8)
include_directories ("${PROJECT_SOURCE_DIR}/src")
include_directories ("${PROJECT_SOURCE_DIR}/lib")

add_executable(racetrackDevice racetrackDevice.c)

target_link_libraries(racetrackDevice iotfdeviceclient )
