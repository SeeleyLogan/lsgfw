cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(lsgfw LANGUAGES C)

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SRC_DIR	"${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_DIR	"${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(TESTS_DIR	"${CMAKE_CURRENT_SOURCE_DIR}/tests")
set(GLFW_DIR	"${LIB_DIR}/glfw-3.4")
set(GLAD_DIR	"${LIB_DIR}/glad")

add_library(lsgfw SHARED "${SRC_DIR}/lsgfw.c")

target_include_directories(lsgfw PUBLIC  ${INCLUDE_DIR} "${GLFW_DIR}/include" ${GLAD_DIR})
target_include_directories(lsgfw PRIVATE ${SRC_DIR})
target_link_directories	  (lsgfw PRIVATE ${LIB_DIR})

add_subdirectory(${GLFW_DIR})
add_subdirectory(${GLAD_DIR})

find_package(OpenMP REQUIRED)

target_link_libraries(lsgfw PUBLIC  OpenMP::OpenMP_C glfw glad)

if (UNIX)
	target_link_libraries(lsgfw PRIVATE m)
 endif()

option(LSGFW_BUILD_TESTS "Build all the test projects found in ./tests" ON)

if (LSGFW_BUILD_TESTS)
	add_subdirectory("${TESTS_DIR}/cube")
endif()

