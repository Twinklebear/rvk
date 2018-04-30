cmake_minimum_required(VERSION 3.5)
project(rvk)
include(CMakePackageConfigHelpers)

if (NOT WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}")

if (WIN32)
	add_definitions(-DNOMINMAX)
endif()

set(CMAKE_MODULE_PATH "${rvk_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
find_package(Threads REQUIRED)
find_package(TurboJpeg REQUIRED)
find_package(Snappy REQUIRED)
find_package(glm REQUIRED)

add_subdirectory(src)

