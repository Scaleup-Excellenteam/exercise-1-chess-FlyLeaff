cmake_minimum_required(VERSION 3.10)
project(Chess)

set(CMAKE_CXX_STANDARD 17)

# Include the directory containing the header files
include_directories(include include/pieces)

# Add the source files
set(SOURCES
    src/main.cpp
    src/Pieces/Rook.cpp
    src/Pieces/MovementStrats.cpp
    src/Pieces/Piece.cpp
    src/Chess.cpp
)

add_executable(Chess ${SOURCES} "src/Board.cpp" "include/Board.h" "include/Game.h" "src/Game.cpp"  "include/ChessNotionParser.h")
