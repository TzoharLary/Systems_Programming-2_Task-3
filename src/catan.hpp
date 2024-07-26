#ifndef CATAN_HPP
#define CATAN_HPP

#include <vector>
#include "Player.hpp"
#include "Board.hpp"

class Catan {
public:
    Catan(Player &p1, Player &p2, Player &p3 , Board& board);
    void ChooseStartingPlayer();
    Board& getBoard();
    void printWinner() const;
    std::vector<Player*> getPlayers();
    


private:
    Player &player1;
    Player &player2;
    Player &player3;
    Board& board;
    Player *currentPlayer;
};

#endif // CATAN_HPP
