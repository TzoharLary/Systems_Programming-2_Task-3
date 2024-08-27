#include <iostream>
#include <vector>
#include "catan.hpp"
#include "Player.hpp"
#include "Board.hpp"

using namespace std;
Catan* globalCatan = nullptr;


int main() {
    Board board;
    Player p1("Amit", board);
    Player p2("Yossi", board);
    Player p3("Dana", board);
    Catan catan(p1, p2, p3, board);
    globalCatan = &catan;

    /* test for place a road not connected to a settlement 
    // 1. place a road near nothing
    p1.placeRoad(1);

    2. place a road near a settlement that not  belong to the player
    p1.placeSettlement(2);
    p2.placeRoad(1);
    */

    /* test for place a road not near anothe road of the player
            p1.placeSettlement(2);
            p1.placeRoad(1);
            p2.placeRoad(0);
    */

    // some code for starting the game
    p1.placeSettlement(10);
    p1.placeRoad(8);
    catan.advanceTurn();
    p2.placeSettlement(12);
    p2.placeRoad(10);
    catan.advanceTurn();
    p3.placeSettlement(19);
    p3.placeRoad(16);
    catan.advanceTurn();
    p3.placeSettlement(23);
    p3.placeRoad(20);
    catan.advanceTurn();
    p2.placeSettlement(30);
    p2.placeRoad(26);
    catan.advanceTurn();
    p1.placeSettlement(35);
    p1.placeRoad(66);
    p1.status();
    p2.status();
    p3.status();
    catan.advanceTurn();
    p1.status();
    p2.status();
    p3.status();
    // p1.placeSettlement(15);
    // print the current player name
    // cout << "Current player: " << catan.getCurrentPlayerName() << endl;
    // cout << "did we after the start of the game?" << p1.getIsAfterStartGame() << endl;
 
 
 
    /* buy for the player all the development card
    for (int i = 0; i < 25; i++) {
        p1.buyDevelopmentCard();   
    }
    */

   /* Some code for start game
     p1.placeSettlement(10);
    p1.placeRoad(8);
    catan.advanceTurn();
    p2.placeSettlement(12);
    p2.placeRoad(10);
    catan.advanceTurn();
    p3.placeSettlement(19);
    p3.placeRoad(16);
    catan.advanceTurn();
    p3.placeSettlement(23);
    p3.placeRoad(20);
    catan.advanceTurn();
    p2.placeSettlement(30);
    p2.placeRoad(26);
    catan.advanceTurn();
    p1.placeSettlement(35);
    p1.placeRoad(66);
    p1.status();
    p2.status();
    p3.status();
    catan.advanceTurn();
   */
    
    /* All the options for the useDevelopmentCard function
    // p1.useDevelopmentCard("Monopoly Ore");
    // p1.useDevelopmentCard("RoadBuilding 0 1");
    // p1.useDevelopmentCard("YearOfPlenty Ore Wheat");
    // p1.useDevelopmentCard("Knight");
    */

    /* test for checking if the value of the vertex is correct on the field that 
    *  holding a vector of pointers to the vertices on the tile
    Tile t1 = board.getTile(1);
    t1.status();
    const Vertex* v10 = board.getTile(1).getVertex(10);
    cout << "The status of vertex 10 is: " << endl;
    v10->status();  
    */


    /* test for checking the Trade function
    p1.Trade(p2, ResourceType::WOOD, 5, ResourceType::BRICK, 5);
    */
    
    /* test for buying a development card
    */
    
    /* test for using a development card that the player dont have

    */
    
    /* test for
    */
    
    /*
    printf("after creating the first settlement and road of p1\n");
    p1.placeSettlement(2, board);
    printf("after creating the second settlement of p1\n");
    for (ResourceType r : {ResourceType::ORE, ResourceType::BRICK, ResourceType::WOOD, ResourceType::WHEAT, ResourceType::SHEEP}) {
        p1.addResource(r, 20);
    }
    p1.status();
    p2.status();
    std::cout << "Before trade: "<< std::endl;
    p1.Trade(p2, ResourceType::WOOD, 5, ResourceType::BRICK, 5);
    std::cout << "After trade: " << std::endl;
    p1.status();
    p2.status();
    // p1.placeSettlement(0, board);
    // p1.placeRoad(0, board);
    // p1.placeSettlement(10, board);
    // p1.placeRoad(9, board);
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
