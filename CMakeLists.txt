cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(lsgfw LANGUAGES C)

option(LSGFW_BUILD_TESTS "Build all the test projects found in ./tests" ON)
option(LSGFW_BUILD_ESSENTIALS "Build essential scripts" ON)

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SRC_DIR		"${CMAKE_CURRENT_SOURCE_DIR}/src")
set(DEP_DIR		"${CMAKE_CURRENT_SOURCE_DIR}/dependencies")
set(TESTS_DIR	"${CMAKE_CURRENT_SOURCE_DIR}/tests")
set(ESS_DIR		"${CMAKE_CURRENT_SOURCE_DIR}/essentials")

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
endif()

add_library(lsgfw SHARED "${SRC_DIR}/lsgfw.c")
target_compile_definitions(lsgfw PRIVATE LSGFW_API_EXPORT)

target_include_directories(lsgfw PUBLIC  ${INCLUDE_DIR} ${DEP_DIR})
target_include_directories(lsgfw PRIVATE ${SRC_DIR})
target_link_directories	  (lsgfw PRIVATE ${DEP_DIR})

find_package(OpenMP REQUIRED)

target_link_libraries(lsgfw PRIVATE OpenMP::OpenMP_C glfw)

if (UNIX)
	target_link_libraries(lsgfw PRIVATE m)
endif()

if (LSGFW_BUILD_TESTS)
	add_subdirectory("${TESTS_DIR}/cube")
endif()

if (LSGFW_BUILD_ESSENTIALS)
	add_subdirectory("${ESS_DIR}/lsgfw_shaders")
	add_subdirectory("${ESS_DIR}/lsgfw_script_utils")
	add_subdirectory("${ESS_DIR}/lsgfw_buffers")
endif()
