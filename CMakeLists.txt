cmake_minimum_required(VERSION 3.7)
project(foodPlanner)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Server.cpp Server.h)

find_package(Boost COMPONENTS system filesystem REQUIRED)

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_executable(foodPlanner ${SOURCE_FILES})

target_link_libraries(foodPlanner
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        )