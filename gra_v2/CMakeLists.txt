cmake_minimum_required(VERSION 3.10)
project(game)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set (CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

link_libraries(stdc++fs)

add_library(game_lib src/pawn.cpp src/queen.cpp src/board.cpp src/position.cpp src/gui.cpp)

add_executable(checkers
        src/main.cpp)
target_link_libraries(checkers game_lib)
target_link_libraries(game_lib SDL2::Main SDL2::TTF)
target_include_directories(game_lib PUBLIC include)
