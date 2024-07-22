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
    
    catan.ChooseStartingPlayer();  // Randomly choose starting player.
    
    Board board = catan.getBoard(); // Get the board from the game.

    printf("after creating the board\n");
    int places1 = 20; // the num of the places of the settlement of the player
    p1.placeSettlement(places1, board);
    int road1 = 18;
    p1.placeRoad(road1, board);
    
    int places2 = 23;
    p1.placeSettlement(places2, board);
    int road2 = 24;
    p1.placeRoad(road2, board); 

   
    
    catan.printWinner(); // No winner yet.

    return 0;
}
