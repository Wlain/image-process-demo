cmake_minimum_required(VERSION 3.27)
project(image_process_demo)

set(CMAKE_CXX_STANDARD 20)

# opencv
find_package(OpenCV REQUIRED)

include_directories(
        ${PROJECT_SOURCE_DIR}/source
        ${OpenCV_INCLUDE_DIRS}
)

add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/source/*.cpp)

add_executable(image_process_demo ${SOURCES})
target_link_libraries(image_process_demo ${OpenCV_LIBS})
