cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(glad LANGUAGES C)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(glad SHARED ${SRC_DIR}/glad.c)

target_compile_definitions(glad PRIVATE GLAD_GLAPI_EXPORT_BUILD)

target_include_directories(glad PRIVATE ${SRC_DIR})

