cmake_minimum_required(VERSION 2.8)
project(IFrameModifyTest)

set(CMAKE_CXX_STANDARD "17")
aux_source_directory(./ files)

add_executable(${PROJECT_NAME} ${files})