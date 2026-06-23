cmake_minimum_required(VERSION 3.16)

project(lvgl_playground LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/lvgl)

find_package(SDL2 REQUIRED)

add_executable(
    lvgl_playground
    src/main.cpp
)

target_include_directories(
    lvgl_playground
    PRIVATE
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(
    lvgl_playground
    PRIVATE
    lvgl
    SDL2::SDL2
)