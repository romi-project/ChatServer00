cmake_minimum_required(VERSION 3.13)
project(RMLib VERSION 0.1.0)

add_library(${PROJECT_NAME} hello.cpp)

target_include_directories(${PROJECT_NAME}
  PUBLIC ../plog/include include
)
