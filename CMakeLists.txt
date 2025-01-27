cmake_minimum_required(VERSION 3.27)
project(image_process_demo)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        ${PROJECT_SOURCE_DIR}/source
        ${PROJECT_SOURCE_DIR}/source/utils
        ${PROJECT_SOURCE_DIR}/3rdparty/stb
)

add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/source/*.cpp)

file(GLOB_RECURSE TESTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)

foreach (TEST ${TESTS})
    get_filename_component(PROJECT_NAME ${TEST} NAME_WE)
    add_executable(${PROJECT_NAME} ${SOURCES} ${TEST})
endforeach ()

