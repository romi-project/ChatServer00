cmake_minimum_required(VERSION 3.13)
project(ChatServer00 VERSION 0.1.0)

if(MSVC)
  string (REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS_INIT "${CMAKE_CXX_FLAGS_INIT}")
  string (REPLACE "/Zi" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
  add_compile_options(/W4 /WX /Z7 /source-charset:utf-8) # /fsanitize=address
else()
  add_compile_options(-Wall -Werror -Wextra -g)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(plog)
add_subdirectory(RMLib)
add_subdirectory(srcs)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/plog/include
    ${CMAKE_SOURCE_DIR}/cxxopts/include
    ${CMAKE_SOURCE_DIR}/RMLib/include
)

# https://runebook.dev/ko/docs/cmake/policy/cmp0079 (3.13)
target_link_libraries(${PROJECT_NAME}
  PUBLIC RMLib
)
