cmake_minimum_required(VERSION 3.15)
project(funni-marching)

find_package(raylib 4.0 REQUIRED) # Requires at least version 4.0

set(CMAKE_C_STANDARD 17) 
set(CMAKE_CXX_STANDARD 17) 

include_directories(/usr/include /usr/local/include) # might need this

file(GLOB SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} raylib)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()