cmake_minimum_required(VERSION 3.10)
project(Minesweeper)

set(CMAKE_BUILD_RPATH "/opt/homebrew/lib")

find_package(SFML COMPONENTS Graphics Audio Window System REQUIRED)

add_executable(Minesweeper src/main.cpp)

target_link_libraries(Minesweeper PRIVATE SFML::Graphics SFML::Audio SFML::Window SFML::System)