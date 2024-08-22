#include "catan.hpp"
#include "Player.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Catan::Catan(Player &p1, Player &p2, Player &p3, Board& board) : player1(p1), player2(p2), player3(p3), board(board), currentTurn(0), phase(FirstRound) {
    ChooseStartingPlayer();
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

Player* Catan::getCurrentPlayer() const {
    return currentPlayer;
}

void Catan::advanceTurn() {
    // this is the first round of placing settlements
    if (isFirstRound()) {
        if (phase == FirstRound) {
            currentTurn++;
            if (currentTurn == 3) {
                phase = SecondRound;
                currentTurn = 2;
            }
        // this is the second round of placing settlements
        } else if (phase == SecondRound) {
            currentTurn--;
            if (currentTurn < 0) {
                phase = RegularPlay;
                currentTurn = 0;
            }
        }
    // this is the regular play phase
    } else {
        currentTurn = (currentTurn + 1) % 3;
    }

    currentPlayer = (currentTurn == 0) ? &player1 : (currentTurn == 1) ? &player2 : &player3;
}

bool Catan::isFirstRound() {

    if (player1.getPoints() < 3 && player2.getPoints() < 3 && player3.getPoints() < 3){
        return true;
    }
    else {
        player1.setafterStartGame(true);
        player2.setafterStartGame(true);
        player3.setafterStartGame(true);
        return false;
    }
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


