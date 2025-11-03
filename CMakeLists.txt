cmake_minimum_required(VERSION 3.15)
set(CMAKE_TOOLCHAIN_FILE external/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "")

project(life)

find_package(raylib CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

set(CMAKE_C_STANDARD 11)

file (GLOB_RECURSE Sources CONFIGURE_DEPENDS "src/*.cpp")
file (GLOB_RECURSE Headers CONFIGURE_DEPENDS "src/*.hpp")

add_executable(${PROJECT_NAME} ${Sources} ${Headers})
target_link_libraries(${PROJECT_NAME} raylib glfw)

if (APPLE)
    # for raylib compatibility
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
