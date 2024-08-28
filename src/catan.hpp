#ifndef CATAN_HPP
#define CATAN_HPP

#include "Board.hpp"
#include <vector>
using std::vector;

class Player;


class Catan {
public:
    Catan(Player &p1, Player &p2, Player &p3 , Board& board);
    Board& getBoard();
    static void checkWinner();
    static vector<Player*> getPlayers();
    bool isFirstRound();
    void advanceTurn();
    Player* getCurrentPlayer() const;     
    string getCurrentPlayerName() const;
    static vector<Player*> allPlayers;


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
