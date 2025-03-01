cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(lsgfw_global_sharing LANGUAGES C)

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SRC_DIR		"${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(lsgfw_global_sharing SHARED "${SRC_DIR}/lsgfw_global_sharing.c")

target_compile_definitions(lsgfw_global_sharing PRIVATE LSGFW_SCRIPT)

target_include_directories(lsgfw_global_sharing PRIVATE ${INCLUDE_DIR})

target_link_libraries(lsgfw_global_sharing PRIVATE lsgfw)

