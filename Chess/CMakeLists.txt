cmake_minimum_required(VERSION 3.10)
project(Chess)

set(CMAKE_CXX_STANDARD 17)

# Include the directory containing the header files
include_directories(include)
include_directories(include/pieces)
# Add the source files

set(SOURCES
    src/Chess.cpp
    src/main.cpp
    src/Board.cpp
    src/Game.cpp
    src/pieces/Piece.cpp
    src/Pieces/Rook.cpp
    src/Pieces/King.cpp
    src/MovementStrats.cpp
)

    
# Add the executable
add_executable(Chess ${SOURCES} "include/pieces/Bishop.h" "include/pieces/Queen.h" "src/pieces/Bishop.cpp" "src/pieces/Queen.cpp" "include/ConstUtils.h" "include/pieces/Knight.h" "src/pieces/Knight.cpp" "src/pieces/Pawn.cpp" "include/pieces/Pawn.h")
