cmake_minimum_required(VERSION 3.15)
project(funni-marching)

find_package(raylib 4.0 REQUIRED) # Requires at least version 4.0

set(CMAKE_C_STANDARD 17) 
set(CMAKE_CXX_STANDARD 17) 

include_directories(/usr/include /usr/local/include) # might need this

# add executiable libs
file(GLOB SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

# add internal 2D libs
file(GLOB 2D_LIBS src/2D/*.cpp)

add_library(${PROJECT_NAME}-2d-libs ${2D_LIBS})

target_link_libraries(${PROJECT_NAME} raylib)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-2d-libs)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()