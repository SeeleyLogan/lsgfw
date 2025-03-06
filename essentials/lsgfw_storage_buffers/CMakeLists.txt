cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(lsgfw_storage_buffers LANGUAGES C)

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SRC_DIR		"${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(lsgfw_storage_buffers SHARED "${SRC_DIR}/lsgfw_storage_buffers.c")

target_compile_definitions(lsgfw_storage_buffers PRIVATE LSGFW_SCRIPT)

target_include_directories(lsgfw_storage_buffers PRIVATE ${INCLUDE_DIR})

target_link_libraries(lsgfw_storage_buffers PRIVATE lsgfw)
