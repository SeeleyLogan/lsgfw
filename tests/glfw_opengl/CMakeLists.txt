cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(cube LANGUAGES C)

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SRC_DIR		"${CMAKE_CURRENT_SOURCE_DIR}/src")

set(PLUGS_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../include")
set(PLUGS_DEP_DIR	  "${CMAKE_CURRENT_SOURCE_DIR}/../../dependencies")

add_executable(glfw_opengl "${SRC_DIR}/main.c")

set_target_properties(glfw_opengl
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/src"
)

if (UNIX)
	target_link_libraries(glfw_opengl PUBLIC m)
endif()

target_include_directories(glfw_opengl PRIVATE ${INCLUDE_DIR} ${PLUGS_INCLUDE_DIR} ${PLUGS_DEP_DIR})

#file(GLOB_RECURSE asset_files "${CMAKE_CURRENT_SOURCE_DIR}/assets/*")

#foreach(asset_file ${asset_files})
#    file(RELATIVE_PATH rel_path "${CMAKE_CURRENT_SOURCE_DIR}" "${asset_file}")
#    get_filename_component(dir_path "${rel_path}" DIRECTORY)
#    file(COPY ${asset_file} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/src/${dir_path}/")
#endforeach()

add_subdirectory("${SRC_DIR}/scripts")