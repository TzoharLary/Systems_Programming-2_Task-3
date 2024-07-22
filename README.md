# Catan Game

## Overview
This project implements a simplified version of the Catan board game in C++. The implementation includes classes for the board, players, and the game logic, adhering to the provided rules.

## Files
- `src/board.hpp` and `src/board.cpp`: Defines and implements the Board class.
- `src/player.hpp` and `src/player.cpp`: Defines and implements the Player class.
- `src/catan.hpp` and `src/catan.cpp`: Defines and implements the Catan class.
- `src/main.cpp`: The main entry point of the application demonstrating one round of the game.
- `tests/tests.cpp`: Unit tests for the classes.
- `Makefile`: Build configuration.
- `README.md`: This file.

## Building and Running
To build the project, run:
```
make
```

To run the tests, run:
```
make test
./run_tests
```

## Usage
Run the main program with:
```
./catan
```

## Class Hierarchy and Methods
### Board
Handles the game board and its setup.
### Player
Represents a player and handles actions such as placing settlements and roads.
### Catan
Manages the overall game flow including turn-taking and determining the winner.

## Dependencies
- g++
- Google Test (for unit tests)

## Contact
For any questions, please contact [your_email@example.com].
