cmake_minimum_required(VERSION 3.10)
project(Minesweeper)

set(CMAKE_BUILD_RPATH "/opt/homebrew/lib")

find_package(SFML COMPONENTS Graphics Audio Window System REQUIRED)

add_executable(Minesweeper
    src/main.cpp
    src/Cell.cpp
    src/Board.cpp
)

target_include_directories(Minesweeper PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(Minesweeper PRIVATE SFML::Graphics SFML::Audio SFML::Window SFML::System)