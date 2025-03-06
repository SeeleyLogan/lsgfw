cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(lsgfw_shaders LANGUAGES C)

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SRC_DIR		"${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(lsgfw_shaders SHARED "${SRC_DIR}/lsgfw_shaders.c")

target_compile_definitions(lsgfw_shaders PRIVATE LSGFW_SCRIPT)

target_include_directories(lsgfw_shaders PRIVATE ${INCLUDE_DIR})

target_link_libraries(lsgfw_shaders PRIVATE lsgfw)
