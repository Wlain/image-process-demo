cmake_minimum_required(VERSION 3.27)
project(image_process_demo)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        ${PROJECT_SOURCE_DIR}/source
)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/source/*.cpp)

add_executable(image_process_demo ${SOURCES})
