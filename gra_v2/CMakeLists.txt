cmake_minimum_required(VERSION 3.10)
project(game)

set (CMAKE_CXX_STANDARD 17)

link_libraries(stdc++fs)

add_library(game_lib src/pawn.cpp src/queen.cpp src/board.cpp src/position.cpp)
target_include_directories(game_lib PUBLIC include)

add_executable(chess_game
        src/main.cpp)
target_link_libraries(chess_game game_lib)
