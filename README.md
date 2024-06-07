# Chess Project

This is a C++ implementation of a chess game. The project is designed to support basic chess functionality and includes a graphical user interface (GUI) for playing the game. The game handles standard chess rules and movement for most pieces. However, certain advanced chess rules are not yet implemented.

## Features

- Standard chess piece movement
- Turn-based gameplay
- Check detection
- Console-based GUI

## Not Implemented

- **Pawn Promotion**: The game does not yet support promoting a pawn to another piece when it reaches the far side of the board.
- **Castling**: The special king and rook move known as castling is not implemented.
- **En Passant**: The special pawn capture move known as en passant is not implemented.

## Documentation

The project uses Doxygen for documentation. The HTML documentation files can be found in the `docs/html` directory. You can open the `annotated.html` file to start browsing the documentation.

[View Doxygen Documentation]([Chess/docs/html/annotated.html](https://scaleup-excellenteam.github.io/exercise-1-chess-FlyLeaff/))

## Getting Started

### Prerequisites

- C++ compiler supporting C++17
- CMake (version 3.10 or higher)
- Doxygen (for generating documentation)
- Graphviz (optional, for generating diagrams in the documentation)

### Building the Project

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/yourrepository.git
    ```

2. Navigate to the project directory:
    ```sh
    cd yourrepository
    ```

3. Create a build directory and navigate into it:
    ```sh
    mkdir build
    cd build
    ```

4. Run CMake to configure the project:
    ```sh
    cmake ..
    ```

5. Build the project:
    ```sh
    cmake --build .
    ```

### Running the Game

After building the project, you can run the game executable from the build directory:
```sh
./Chess
