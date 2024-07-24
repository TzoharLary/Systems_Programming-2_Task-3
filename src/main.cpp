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
    // return 0;

    catan.ChooseStartingPlayer();  // Randomly choose starting player.
    
    Board board = catan.getBoard(); // Get the board from the game.


    p1.placeSettlement(20, board);
    p1.placeRoad(18, board);
    printf("after creating the first settlement and road of p1\n");
    p2.placeSettlement(15, board);
    p2.placeRoad(2, board); 
    printf("after creating the first settlement and road of p2\n");
    p3.placeSettlement(10, board);
    p3.placeRoad(3, board);
    printf("after creating the first settlement and road of p3\n");
    


   
    
    catan.printWinner(); // No winner yet.

    return 0;
}
