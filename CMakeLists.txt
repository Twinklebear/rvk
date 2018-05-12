cmake_minimum_required(VERSION 3.5)
project(rvk)
include(CMakePackageConfigHelpers)
include(GenerateExportHeader)

if (NOT WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
else()
	add_definitions(-DNOMINMAX)
	add_definitions(-DWIN32_LEAN_AND_MEAN)
endif()

# Aren't these concated anyways?
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}")

set(CMAKE_MODULE_PATH "${rvk_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
find_package(Threads REQUIRED)
find_package(TurboJpeg REQUIRED)
find_package(Snappy REQUIRED)
find_package(glm REQUIRED)

add_subdirectory(src)
add_subdirectory(tests)

