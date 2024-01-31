cmake_minimum_required(VERSION 3.23)
project(chk_window)

add_subdirectory("external/chk_common")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("external/glfw")

add_library(chk_window)
target_sources(chk_window PRIVATE
    "src/window/window.hpp"
    "src/window/window.cpp"
)
target_link_libraries(chk_window PRIVATE chk_common)
target_link_libraries(chk_window PRIVATE glfw)

target_compile_features(chk_window PRIVATE cxx_std_20)
target_include_directories(chk_window INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src")
