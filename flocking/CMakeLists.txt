SET(APP_NAME Flocking)
project(${APP_NAME})

cmake_minimum_required(VERSION 2.8)

#Cmake settings
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_FLAGS "-std=c++11")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/bin)
set(lab1_BINARY_DIR ${PROJECT_SOURCE_DIR}/bin)



#Packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

include_directories(${GLEW_INCLUDE_DIR})
include_directories(${GLFW_INCLUDE_DIRS})

#Project settings
file(GLOB APP_SOURCES src/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/glm)

add_executable(${APP_NAME} ${APP_SOURCES})

target_link_libraries(${APP_NAME} ${GLEW_LIBRARIES} ${GLFW_STATIC_LIBRARIES})
