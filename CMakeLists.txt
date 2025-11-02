cmake_minimum_required(VERSION 3.15)
set(CMAKE_TOOLCHAIN_FILE external/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "")

project(life)

find_package(raylib CONFIG REQUIRED)

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME} src/main.cc)
target_link_libraries(${PROJECT_NAME} raylib glfw)

if (APPLE)
    # for raylib compatibility
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()