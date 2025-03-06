cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(cube LANGUAGES C)

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SRC_DIR		"${CMAKE_CURRENT_SOURCE_DIR}/src")

add_executable(cube "${SRC_DIR}/main.c")

set_target_properties(cube
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/src"
)

target_include_directories(cube PRIVATE ${INCLUDE_DIR})

target_link_libraries(cube PRIVATE lsgfw)

if (UNIX)
	target_link_libraries(cube PRIVATE m)
endif()

file(GLOB_RECURSE asset_files "${CMAKE_CURRENT_SOURCE_DIR}/assets/*")

foreach(asset_file ${asset_files})
    file(RELATIVE_PATH rel_path "${CMAKE_CURRENT_SOURCE_DIR}" "${asset_file}")
    get_filename_component(dir_path "${rel_path}" DIRECTORY)
    file(COPY ${asset_file} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/src/${dir_path}/")
endforeach()

add_subdirectory("${SRC_DIR}/scripts")
