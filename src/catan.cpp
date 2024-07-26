#include "catan.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Catan::Catan(Player &p1, Player &p2, Player &p3, Board& board) : player1(p1), player2(p2), player3(p3), board(board) {
    std::srand(std::time(0));
}

Board& Catan::getBoard() {
    return board;
}

void Catan::ChooseStartingPlayer() {
    int randomPlayer = std::rand() % 3;
    if (randomPlayer == 0) {
        currentPlayer = &player1;
    } else if (randomPlayer == 1) {
        currentPlayer = &player2;
    } else {
        currentPlayer = &player3;
    }
    std::cout << "Starting player: " << currentPlayer->getName() << std::endl;
}

std::vector<Player*> Catan::getPlayers() {
    return { &player1, &player2, &player3 };
}



void Catan::printWinner() const {
    if (player1.getPoints() >= 100) {
        std::cout << "Winner: " << player1.getName() << std::endl;
    } else if (player2.getPoints() >= 100) {
        std::cout << "Winner: " << player2.getName() << std::endl;
    } else if (player3.getPoints() >= 100) {
        std::cout << "Winner: " << player3.getName() << std::endl;
    } else {
        std::cout << "No winner yet." << std::endl;
    }
}
