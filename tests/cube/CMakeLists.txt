cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(cube LANGUAGES C)

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SRC_DIR	"${CMAKE_CURRENT_SOURCE_DIR}/src")

add_executable(cube ${SRC_DIR}/main.c)

target_include_directories(cube PRIVATE ${INCLUDE_DIR} ${SRC_DIR})

target_link_libraries(cube PRIVATE lsgfw)

