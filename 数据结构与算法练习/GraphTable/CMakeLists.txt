cmake_minimum_required(VERSION 2.8)

project(GraphTable)

file(GLOB SOURCES
    *.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
