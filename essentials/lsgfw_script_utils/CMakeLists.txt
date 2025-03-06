cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(lsgfw_script_utils LANGUAGES C)

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SRC_DIR		"${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(lsgfw_script_utils SHARED "${SRC_DIR}/lsgfw_script_utils.c")

target_compile_definitions(lsgfw_script_utils PRIVATE LSGFW_SCRIPT)

target_include_directories(lsgfw_script_utils PRIVATE ${INCLUDE_DIR})

target_link_libraries(lsgfw_script_utils PRIVATE lsgfw)
