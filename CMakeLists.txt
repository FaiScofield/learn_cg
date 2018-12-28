cmake_minimum_required(VERSION 3.2)

project(learn_cg)

set(CMAKE_BUILD_TYPE "Debug")
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(OpenCV REQUIRED)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include
    ${OpenCV_Include_DIR}
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
add_executable(ConvexHull src/ConvexHull.cpp)
target_link_libraries(ConvexHull ${OpenCV_LIBS})

