cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(ls_plugs LANGUAGES C)

set(TESTS_DIR	"${CMAKE_CURRENT_SOURCE_DIR}/tests")

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
endif()

add_subdirectory("${TESTS_DIR}/glfw_opengl")
