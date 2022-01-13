cmake_minimum_required(VERSION 3.15)
project(space)

find_package(raylib 3.0 REQUIRED) # Requires at least version 3.0

set(CMAKE_C_STANDARD 11) # Requires C11 standard

set (CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/window.cpp
    src/gameplay.cpp
    src/weapon.cpp
    src/wp_shotty.cpp
    src/wp_assaultrifle.cpp
    src/wp_enemyslingshot.cpp
    src/terrain.cpp
    src/entity.cpp)

target_link_libraries(${PROJECT_NAME} raylib m pthread dl)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
