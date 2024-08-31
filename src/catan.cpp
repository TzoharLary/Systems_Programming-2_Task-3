#include "catan.hpp"
#include "Player.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
using std::cout;
using std::endl;
using std::srand;
using std::time;

vector<Player*> Catan::allPlayers;

Catan::Catan(Player &p1, Player &p2, Player &p3, Board& board) : player1(p1), player2(p2), player3(p3), board(board), currentTurn(0), phase(FirstRound) {
    currentPlayer = &player1;
    player1.setisMyTurn(true);
    srand(time(0));
    allPlayers.clear();
    if(allPlayers.size() < 3){
        allPlayers.push_back(&player1);
        allPlayers.push_back(&player2);
        allPlayers.push_back(&player3);
    }
    for(Player* player : allPlayers){
        player->setRoundStatus({true, false, false});
    }
}

Board& Catan::getBoard() {
    return board;
}

string Catan::getCurrentPlayerName() const {
    return currentPlayer->getName();
}

vector<Player*> Catan::getPlayers() {
    return allPlayers;
}

Player* Catan::getCurrentPlayer() const {
    return currentPlayer;
}


int Catan::CubeRoll() {
    int roll = (rand() % 12) + 2;
    cout << "The cube rolled: " << roll << endl;
    return roll;
}



/* Explanation of the advanceTurn method:
*  The advanceTurn method is responsible for advancing the turn to the next player.
*  The method follows these steps:
*  1. Set all players to not their turn.
*  2. Set all players to not purchase a development card this turn.
*  3. If it is the first round, increment the current turn in order p1 -> p2 -> p3.
*  4. In the end of the first round, start the second round.
*  5. If it is the second round, decrement the current turn in order p3 -> p2 -> p1.
*  6. In the end of the second round, start the regular play phase for starting the game.
*  7. In the regular play phase, increment the current turn in order p1 -> p2 -> p3.
*  8. Set the current player to their turn.
*  9. Distribute resources to players based on the cube roll.
*/
void Catan::advanceTurn() {
    // set all players to not their turn
    player1.setisMyTurn(false);
    player2.setisMyTurn(false);
    player3.setisMyTurn(false);
    player1.setPurchaseDevelopmentCardThisTurn(false);
    player2.setPurchaseDevelopmentCardThisTurn(false);
    player3.setPurchaseDevelopmentCardThisTurn(false);
    // this is the first round of placing settlements
    if (isFirstRound()) {
        if (phase == FirstRound) {
            currentTurn++;
            if (currentTurn == 3) {
                phase = SecondRound;
                for(Player* player : allPlayers){
                    player->setRoundStatus({false, true, false});
                }
                // We want the next turn to be the last player's. (Dana)
                currentTurn = 2;
            }
        } 
        // this is the second round of placing settlements
        // we used else if, for verifying that if the first condition is true, the second condition will not be checked.
        else if (phase == SecondRound){
            currentTurn--;
            if (currentTurn < 0) {
                phase = RegularPlay;
                for(Player* player : allPlayers){
                    player->setRoundStatus({false, false, true});
                }
                currentTurn = 0;
                currentPlayer = &player1;
                cout << "We start the game" << endl;
                cout << "Now it's " << currentPlayer->getName() << "'s turn." << endl;
                currentPlayer->setisMyTurn(true);
                int cubeRoll = CubeRoll();
                distributeResources(cubeRoll);
                return;
            }
        }
    }
    // this is the regular play phase
    else {
        currentTurn = (currentTurn + 1) % 3;
        // distribute resources to players based on the cube roll
        currentPlayer = (currentTurn == 0) ? &player1 : (currentTurn == 1) ? &player2 : &player3;
        // set the current player to their turn
        currentPlayer->setisMyTurn(true);
        cout << "Now it's " << currentPlayer->getName() << "'s turn." << endl;
        distributeResources(CubeRoll());
        return;
    }
    currentPlayer = (currentTurn == 0) ? &player1 : (currentTurn == 1) ? &player2 : &player3;
    // set the current player to their turn
    currentPlayer->setisMyTurn(true);
    currentPlayer->setPurchaseYOPThisTurn({false, false});
    cout << "Now it's " << currentPlayer->getName() << "'s turn." << endl;
}

void Catan::distributeResources(int rolledNumber){
    // auto& tile: Indicates that the variable tile is a reference to the original variable within the vector board.tiles, preventing unnecessary copying of the tile.
    // const auto& vertex: Indicates that the variable vertex is a const reference to the original Vertex object within the vector tile.vertices, preventing unintended modification and unnecessary copying.
    for (auto& tile : board.tiles) {
        if (tile.getNumber() != rolledNumber){
            continue;
        }
        for (const Vertex* vertex : tile.getVertices()) {
            if (vertex->isOccupied()) {
                Player* PlayerOnThisTile = vertex->getPlayer();
                if (vertex->getType() == Vertex::VertexType::SETTLEMENT) {
                    PlayerOnThisTile->addResource(tile.getResource(), 1);
                } else if (vertex->getType() == Vertex::VertexType::CITY) {
                    PlayerOnThisTile->addResource(tile.getResource(), 2);
                }
            }
            else{
                // cout << "the vertex " << vertex.getId() << " is not occupied" << endl;
            }
        }
    }
}

/* if FirstRound explanation:
*  if all players together have less than 7 points and less than 7 roads, then it is the first round.
*  if not, then it is not the first round
*/
bool Catan::isFirstRound() {
    if ((player1.getPoints() + player2.getPoints() + player3.getPoints() < 7) && (player1.getNumOfRoads() + player2.getNumOfRoads() + player3.getNumOfRoads() < 7) && (phase != RegularPlay)) {
        return true;
    }
    else{
        return false;
    } 
}

void Catan::checkWinner() {
    for (const auto& player : allPlayers) {
        if(player->getPoints() >= 10){
            cout << "The game is over and the winner is: " << player->getName() << "\n" << "This is the status of all the players in the game:" << endl;
            for (const auto& p : allPlayers) {
                p->status();
            }
            exit(0);
        }
    }
}


