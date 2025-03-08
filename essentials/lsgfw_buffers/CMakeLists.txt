cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(lsgfw_buffers LANGUAGES C)

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SRC_DIR		"${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(lsgfw_buffers SHARED "${SRC_DIR}/lsgfw_buffers.c")

target_compile_definitions(lsgfw_buffers PRIVATE LSGFW_SCRIPT)

target_include_directories(lsgfw_buffers PRIVATE ${INCLUDE_DIR})

target_link_libraries(lsgfw_buffers PRIVATE lsgfw)
