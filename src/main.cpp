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

    p1.placeSettlement(0, board);
    p1.placeRoad(0, board);
    p1.placeSettlement(10, board);
    p1.placeRoad(9, board);
    p1.placeRoad(2, board);

    for (ResourceType r : {ResourceType::ORE, ResourceType::BRICK, ResourceType::WOOD, ResourceType::WHEAT, ResourceType::SHEEP}) {
        p1.addResource(r, 100);
        p2.addResource(r, 100);
        p3.addResource(r, 100);
    }



 




    /*
    printf("after creating the first settlement and road of p1\n");
    p1.placeSettlement(2, board);
    printf("after creating the second settlement of p1\n");
    for (ResourceType r : {ResourceType::ORE, ResourceType::BRICK, ResourceType::WOOD, ResourceType::WHEAT, ResourceType::SHEEP}) {
        p1.addResource(r, 20);
    }
    board.printAdjacent(0, false);
    board.printAdjacent(0, true);
    p2.placeSettlement(3, board);
   p1.upgradeSettlementToCity(0, board);
    p1.upgradeSettlementToCity(10, board);
    p1.upgradeSettlementToCity(21, board);
    p1.upgradeSettlementToCity(23, board);
    p1.upgradeSettlementToCity(25, board);
    printf("after creating the third settlement of p1\n");
    p1.placeSettlement(6, board);
    printf("after creating the fourth settlement of p1\n");
    p1.placeSettlement(14, board);
    printf("after creating the fifth settlement of p1\n");
    p1.placeSettlement(25, board);


    p2.placeSettlement(15, board);
    p2.placeRoad(2, board); 
    printf("after creating the first settlement and road of p2\n");
    p3.placeSettlement(10, board);
    p3.placeRoad(3, board);
    printf("after creating the first settlement and road of p3\n");
    */



   
    
    catan.printWinner(); // No winner yet.

    return 0;
}
