cmake_minimum_required(VERSION 3.27)
project(image_process_demo)
set(CMAKE_CXX_STANDARD 20)

include_directories(
        ${PROJECT_SOURCE_DIR}/source
        ${PROJECT_SOURCE_DIR}/source/utils
        ${PROJECT_SOURCE_DIR}/source/algorithm
        ${PROJECT_SOURCE_DIR}/source/mockAIData
        ${PROJECT_SOURCE_DIR}/3rdparty/stb
)

add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/source/*.cpp)

file(GLOB TESTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/*)

foreach (TEST ${TESTS})
    file(GLOB_RECURSE EXAMPLE_SOURCES ${TEST}/*.cpp)
    file(GLOB_RECURSE EXAMPLE_HEADERS ${TEST}/*.h)
    get_filename_component(PROJECT_NAME ${TEST} NAME)
    add_executable(${PROJECT_NAME} ${SOURCES} ${EXAMPLE_SOURCES} ${EXAMPLE_HEADERS}
            source/algorithm/steroNose.cpp
            source/algorithm/steroNose.h
            source/algorithm/lipsRecolor.cpp
            source/algorithm/lipsRecolor.h)
endforeach ()

