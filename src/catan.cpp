#include "catan.hpp"
#include "Player.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Catan::Catan(Player &p1, Player &p2, Player &p3, Board& board) : player1(p1), player2(p2), player3(p3), board(board), currentTurn(0), phase(FirstRound) {
    // ChooseStartingPlayer();
    currentPlayer = &player1;
    player1.setisMyTurn(true);
    std::srand(std::time(0));
}

Board& Catan::getBoard() {
    return board;
}

string Catan::getCurrentPlayerName() const {
    return currentPlayer->getName();
}

// void Catan::ChooseStartingPlayer() {
//     int randomPlayer = std::rand() % 3;
//     if (randomPlayer == 0) {
//         currentPlayer = &player1;
//     } else if (randomPlayer == 1) {
//         currentPlayer = &player2;
//     } else {
//         currentPlayer = &player3;
//     }
//     std::cout << "Starting player: " << currentPlayer->getName() << std::endl;
// }

std::vector<Player*> Catan::getPlayers() {
    return { &player1, &player2, &player3 };
}

Player* Catan::getCurrentPlayer() const {
    return currentPlayer;
}

void Catan::advanceTurn() {
    // set all players to not their turn
    player1.setisMyTurn(false);
    player2.setisMyTurn(false);
    player3.setisMyTurn(false);
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
    // set the current player to their turn
    currentPlayer->setisMyTurn(true);

}

/* if FirstRound explanation:
*  if all players have less than 3 points, then it is the first round
*  if not, then it is not the first round
*  set all players to afterStartGame because the first round is over
*/
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


