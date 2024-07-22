#include <iostream>
#include <vector>
#include "catan.hpp"
#include "Player.hpp"
#include "Board.hpp"

using namespace std;

int main() {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");
    Catan catan(p1, p2, p3);
    printf("after activating catan\n");
    // return 0;

    catan.ChooseStartingPlayer();  // Randomly choose starting player.
    
    Board board = catan.getBoard(); // Get the board from the game.

    printf("after creating the board\n");

    p1.placeSettlement(20, board);
    p1.placeRoad(18, board);
    printf("after creating the first settlement and road of p1\n");
    // int settlement2 = 23;
    // p1.placeSettlement(settlement2, board);
    // int road2 = 24;
    // p1.placeRoad(road2, board); 

   
    
    catan.printWinner(); // No winner yet.

    return 0;
}
