#ifndef CATAN_HPP
#define CATAN_HPP

#include <vector>
// #include "Player.hpp"
#include "Board.hpp"

class Player;


class Catan {
public:
    Catan(Player &p1, Player &p2, Player &p3 , Board& board);
    Board& getBoard();
    void printWinner() const;
    std::vector<Player*> getPlayers();
    bool isFirstRound();
    void advanceTurn();
    Player* getCurrentPlayer() const;     
    string getCurrentPlayerName() const;


private:
    enum TurnPhase { FirstRound, SecondRound, RegularPlay};
    Player &player1;
    Player &player2;
    Player &player3;
    Board& board;
    Player *currentPlayer;
    int currentTurn;
    TurnPhase phase;
    int CubeRoll();
    void distributeResources(int rolledNumber);


};

#endif // CATAN_HPP
