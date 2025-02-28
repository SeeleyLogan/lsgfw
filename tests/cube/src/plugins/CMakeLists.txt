cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(cube LANGUAGES C)

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../include")
set(SRC_DIR	    "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB_RECURSE SCRIPTS_SOURCES "${SRC_DIR}/*.c")

foreach(SCRIPT_SOURCE ${SCRIPTS_SOURCES})
	get_filename_component(SCRIPT_NAME ${SCRIPT_SOURCE} NAME_WE)	

	add_library(${SCRIPT_NAME} SHARED ${SCRIPT_SOURCE})
	
	target_compile_definitions(${SCRIPT_NAME} PRIVATE LSGFW_API_EXPORT)
	target_compile_definitions(${SCRIPT_NAME} PRIVATE LSGFW_SCRIPT)

	target_include_directories(${SCRIPT_NAME} PRIVATE ${INCLUDE_DIR})

	target_link_libraries(${SCRIPT_NAME} PRIVATE lsgfw)
endforeach()
