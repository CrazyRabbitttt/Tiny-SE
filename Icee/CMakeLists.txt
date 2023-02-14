cmake_minimum_required(VERSION 3.14)

project(Icee_Net_Library)

set(CMAKE_CXX_STANDARD 17)

#message(${PROJECT_SOURCE_DIR})

# Includes.
set(ICEE_SRC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/include)

include_directories(${ICEE_SRC_INCLUDE_DIR})

aux_source_directory(${PROJECT_SOURCE_DIR}/src/core CORE_FILE)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/http HTTP_FILE)

add_subdirectory(src)


add_executable(main main.cc)

