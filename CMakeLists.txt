cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(lsgfw LANGUAGES C)

option(LSGFW_BUILD_SHARED_LIBRARY "Build LSGFW as a static import library" ON)
option(LSGFW_BUILD_TESTS "Build all the test projects found in ./tests" ON)

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SRC_DIR	"${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_DIR	"${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(TESTS_DIR	"${CMAKE_CURRENT_SOURCE_DIR}/tests")
set(GLFW_DIR	"${LIB_DIR}/glfw-3.4")
set(GLAD_DIR	"${LIB_DIR}/glad")

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
endif()

if (LSGFW_BUILD_SHARED_LIBRARY)
	add_library(lsgfw SHARED "${SRC_DIR}/lsgfw.c")
	target_compile_definitions(lsgfw PRIVATE LSGFW_API_EXPORT)
else()
	add_library(lsgfw STATIC "${SRC_DIR}/lsgfw.c")
endif()

target_compile_definitions(lsgfw PUBLIC GLAD_GLAPI_EXPORT)

set_target_properties(lsgfw
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/src"
)

target_include_directories(lsgfw PUBLIC  ${INCLUDE_DIR} "${GLFW_DIR}/include" ${GLAD_DIR})
target_include_directories(lsgfw PRIVATE ${SRC_DIR})
target_link_directories	  (lsgfw PRIVATE ${LIB_DIR})

add_subdirectory(${GLFW_DIR})
add_subdirectory(${GLAD_DIR})

find_package(OpenMP REQUIRED)

target_link_libraries(lsgfw PUBLIC OpenMP::OpenMP_C glfw glad)

if (UNIX)
	target_link_libraries(lsgfw PRIVATE m)
endif()

if (LSGFW_BUILD_TESTS)
	add_subdirectory("${TESTS_DIR}/cube")
endif()

