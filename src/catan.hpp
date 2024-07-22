#ifndef CATAN_HPP
#define CATAN_HPP

#include "Player.hpp"
#include "Board.hpp"

class Catan {
public:
    Catan(Player &p1, Player &p2, Player &p3);
    void ChooseStartingPlayer();
    Board getBoard() const;
    void printWinner() const;

private:
    Player &player1;
    Player &player2;
    Player &player3;
    Board board;
    Player *currentPlayer;
};

#endif // CATAN_HPP
