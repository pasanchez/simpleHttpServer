cmake_minimum_required(VERSION 3.7)
project(simpleHttpServer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        example/main.cpp
        Server.cpp
        Server.h
        example/jsoncpp.cpp
        example/json/json.h
        example/json/json-forwards.h
        )

find_package(Boost REQUIRED COMPONENTS system)

add_executable(simpleHttpServer ${SOURCE_FILES})

target_link_libraries(simpleHttpServer boost_system)