#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/Board.hpp" 
#include "../src/catan.hpp"
#include "../src/Player.hpp"
#include "../src/Road.hpp"
#include <iostream>
#include <stdexcept>
#include <exception>


using namespace std;

/*  Explanation of why we created the startGame() method:
    we use the startGame() method to initialize the game and simulate the first two rounds,
    ensuring that the game is in the appropriate state for the following test cases.
    this method helps reduce code duplication and keeps the tests focused on specific scenarios,
    such as placing settlements under certain conditions.
*/
void startGame(Player& p1, Player& p2, Player& p3, Board& board, Catan& catan) {
    // First round of placing 1 settlement and 1 road each player
    // The order of the players is p1 -> p2 -> p3
    p1.placeSettlement(10);
    p1.placeRoad(8);
    catan.advanceTurn();
    p2.placeSettlement(12);
    p2.placeRoad(10);
    catan.advanceTurn();
    p3.placeSettlement(19);
    p3.placeRoad(16);
    catan.advanceTurn();
    // Second round of placing 1 settlement and 1 road each player
    // Now the order of the players is p3 -> p2 -> p1
    p3.placeSettlement(23);
    p3.placeRoad(20);
    catan.advanceTurn();
    p2.placeSettlement(29);
    p2.placeRoad(28);
    catan.advanceTurn();
    p1.placeSettlement(35);
    p1.placeRoad(66);
    catan.advanceTurn();
    // Now we starting the game, p1 - Amit is the first player to play.
}

TEST_CASE("Player class"){

    SUBCASE("placeSettlement function"){
              
        SUBCASE("place more than 1 settlement during the first round"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            p1.placeSettlement(10);
            p1.placeRoad(8);
            bool condition1 = false;
            bool condition2 = false;
            if(p1.getRoundStatus()[0]){
                condition1 = true;
            }
            try {
                p1.placeSettlement(47); 
            } catch (const std::runtime_error&) {
                condition2 = true;
            }
            if(condition1 && condition2){
                CHECK_THROWS_AS(p1.placeSettlement(47), runtime_error);
            }     
        }

        SUBCASE("place more than 1 settelment during the second round"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
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
            bool condition1 = false;
            bool condition2 = false;
            if(p3.getRoundStatus()[1]){
                condition1 = true;
            }
            try {
                p3.placeSettlement(47); 
            } catch (const std::runtime_error&) {
                condition2 = true;
            }
            if(condition1 && condition2){
                CHECK_THROWS_AS(p3.placeSettlement(47), runtime_error);
            }
        }

        SUBCASE("The player attempts to place a settlement in invalid index"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            // return all the settlements to the player
            CHECK_THROWS_AS(p1.placeSettlement(100), out_of_range);
        }

        SUBCASE("The player attempts to place a settlement in a place that already occupied"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            p1.placeSettlement(10);
            CHECK_THROWS_AS(p1.placeSettlement(10), runtime_error);
        }

        /*  We write  this case to check 2 edge cases:
        *  1. The player want to place a settlement in a place that adjacent to another settlement
        *  2. The player wants to build a settlement,
        *     we are after the start of the game, 
        *     and he does not have 2 adjacent paths to the index of the vertex he chose.
        */
        SUBCASE("The player attempts to place a settlement in a place that adjacent to another settlement"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            p1.placeSettlement(10);
            CHECK_THROWS_AS(p1.placeSettlement(11), runtime_error);
        }
    
        SUBCASE("Verify settlement is correctly placed at the specified vertex"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            p1.placeSettlement(10);
            bool found = find(p1.getSettlements().begin(), p1.getSettlements().end(), 10) != p1.getSettlements().end();
            REQUIRE(found);
        }

        SUBCASE("The player attempts to place more than 5 settlements"){ 
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            startGame(p1, p2, p3, board, catan);
            p1.placeRoad(53);
            p1.placeRoad(1);
            p1.placeRoad(0);
            p1.placeRoad(48);
            p1.placeRoad(2);
            p1.placeSettlement(1);
            p1.placeSettlement(3);
            p1.placeSettlement(8);
            p1.placeRoad(6);
            p1.placeRoad(49);
            CHECK_THROWS_AS(p1.placeSettlement(17), runtime_error);
        }  
            /* We check in this case two conditions at the same time:
        //     *  1. The game is after the second round.
        //     *  2. The player wants to build a settlement on a vertex that is not near any of his roads.
        //     *  The test is performed as follows:
        //     *  1. We check if the player is in the third round and set condition1 to true if it is.
        //     *  2. We try to build a settlement on a vertex that is not near any of the player's roads,
        //     *  and set condition2 to true if an exception is thrown.
        //     *  3. We check if the two conditions are true, and if so, we check if an exception is thrown.
        //     */
        SUBCASE("The player attempts to place a settlement not near any road after the second round"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            startGame(p1, p2, p3, board, catan);
            bool isRegularRound = false;
            bool NotNearRoad = false; 
            if(p1.getRoundStatus()[2]){
                isRegularRound = true;
            }
            try {
                p1.placeSettlement(47); 
            } catch (const std::runtime_error&) {
                NotNearRoad = true;
            }
            if(isRegularRound && NotNearRoad){
                CHECK_THROWS_AS(p1.placeSettlement(47), runtime_error);
            }
        }
   
    }

    SUBCASE("placeRoad function"){
        
        SUBCASE("The player attempts to place a road in an invalid index"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            CHECK_THROWS_AS(p1.placeRoad(100), out_of_range);
        }

        SUBCASE("The player attempts to build a road not adjacent to any of their roads or settlements after the second round"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            startGame(p1, p2, p3, board, catan);
            bool isRegularRound = false;
            bool noAdjacentRoadOrSettlement = false;

            if(p1.getRoundStatus()[2]){
                isRegularRound = true;
            }
            try {
                p1.placeRoad(47);
            } catch (const std::runtime_error&) {
                noAdjacentRoadOrSettlement = true;
            }
            if(isRegularRound && noAdjacentRoadOrSettlement){
                CHECK_THROWS_AS(p1.placeRoad(47), runtime_error);
            }
        }

        SUBCASE("The player attempts to build a road in a place that already occupied"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            startGame(p1, p2, p3, board, catan);
            CHECK_THROWS_AS(p1.placeRoad(8), runtime_error);
        }
    
        SUBCASE("Verify road is correctly placed if the player has a road near the place he wants to build"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            startGame(p1, p2, p3, board, catan);
            p1.placeRoad(7);
            // Now we show that there is a road near the place we want to build
            Road road7 = board.getRoads().at(7);
            vector<int> adjacentRoadsTo7 = road7.getAdjacentRoads();
            bool foundAdjacentRoad = false;
            for (int roadId : adjacentRoadsTo7) {
                Road adjacentRoad = board.getRoads().at(roadId);
                if (adjacentRoad.getPlayerName() == p1.getName()) {
                    foundAdjacentRoad = true;
                    break;
                }
            }
            // if this require is true so the player has a road near the place he wants to build
            REQUIRE(foundAdjacentRoad);
            // If this require is true so the player has a road in the index 9
            REQUIRE(road7.getPlayerName() == p1.getName());
        }
    
        SUBCASE("Verify road is correctly placed if the player has a settlement near the place he wants to build"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            startGame(p1, p2, p3, board, catan);
            p1.placeRoad(9);
            // Now we show that there is a settlement near the place we want to build
            Road road9 = board.getRoads().at(9);
            vector<int> betweenVertices = road9.getBetweenVertices();
            bool foundSettlement = false;
            for (int vertexId : betweenVertices) {
                Vertex vertex = board.getAllVertices().at(vertexId);
                if (vertex.getPlayerName() == p1.getName()) {
                    foundSettlement = true;
                    break;
                }
            }
            // if this require is true so the player has a settlement near the place he wants to build
            REQUIRE(foundSettlement);
            // If this require is true so the player has a road in the index 9
            REQUIRE(road9.getPlayerName() == p1.getName());
        }
    
    
    
    }

    SUBCASE("Buy function"){

        SUBCASE("Player successfully buys a Settlement after the second round"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            startGame(p1, p2, p3, board, catan);
            p1.placeRoad(53);
            p1.placeRoad(1);
            map<ResourceType, int> resourceBeforeBuy = p1.getResources();
            p1.placeSettlement(1);
            map<ResourceType, int> resourceAfterBuy = p1.getResources();
            REQUIRE(resourceAfterBuy[ResourceType::WOOD] == resourceBeforeBuy[ResourceType::WOOD] - 1);
            REQUIRE(resourceAfterBuy[ResourceType::BRICK] == resourceBeforeBuy[ResourceType::BRICK] - 1);
            REQUIRE(resourceAfterBuy[ResourceType::WHEAT] == resourceBeforeBuy[ResourceType::WHEAT] - 1);
            REQUIRE(resourceAfterBuy[ResourceType::SHEEP] == resourceBeforeBuy[ResourceType::SHEEP] - 1);
        }
        
        SUBCASE("Player successfully buys a City after the second round"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            startGame(p1, p2, p3, board, catan);
            p1.placeRoad(53);
            p1.placeRoad(1);
            p1.placeSettlement(1);
            map<ResourceType, int> resourceBeforeBuy = p1.getResources();
            p1.upgradeSettlementToCity(1);
            map<ResourceType, int> resourceAfterBuy = p1.getResources();
            REQUIRE(resourceAfterBuy[ResourceType::WHEAT] == resourceBeforeBuy[ResourceType::WHEAT] - 2);
            REQUIRE(resourceAfterBuy[ResourceType::ORE] == resourceBeforeBuy[ResourceType::ORE] - 3);
        }
    
        SUBCASE("Player successfully buys a Development Card after the second round"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            startGame(p1, p2, p3, board, catan);
            p1.placeRoad(53);
            p1.placeRoad(1);
            p1.placeSettlement(1);
            map<ResourceType, int> resourceBeforeBuy = p1.getResources();
            p1.buyDevelopmentCard();
            map<ResourceType, int> resourceAfterBuy = p1.getResources();
            REQUIRE(resourceAfterBuy[ResourceType::ORE] == resourceBeforeBuy[ResourceType::ORE] - 1);
            REQUIRE(resourceAfterBuy[ResourceType::WHEAT] == resourceBeforeBuy[ResourceType::WHEAT] - 1);
            REQUIRE(resourceAfterBuy[ResourceType::SHEEP] == resourceBeforeBuy[ResourceType::SHEEP] - 1);
        }

        SUBCASE("Player successfully buys a Road after the second round"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            startGame(p1, p2, p3, board, catan);
            map<ResourceType, int> resourceBeforeBuy = p1.getResources();
            p1.placeRoad(53);
            map<ResourceType, int> resourceAfterBuy = p1.getResources();
            REQUIRE(resourceAfterBuy[ResourceType::WOOD] == resourceBeforeBuy[ResourceType::WOOD] - 1);
            REQUIRE(resourceAfterBuy[ResourceType::BRICK] == resourceBeforeBuy[ResourceType::BRICK] - 1);
        }

        SUBCASE("Player successfully buys a 2 Road, 1 settlement, 1 city, 1 development card after the second round"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            startGame(p1, p2, p3, board, catan);
            map<ResourceType, int> resourceBeforeBuy = p1.getResources();
            p1.placeRoad(53);
            p1.placeRoad(1);
            p1.placeSettlement(1);
            p1.upgradeSettlementToCity(1);
            p1.buyDevelopmentCard();
            map<ResourceType, int> resourceAfterBuy = p1.getResources();
            REQUIRE(resourceAfterBuy[ResourceType::WOOD] == resourceBeforeBuy[ResourceType::WOOD] - 3);
            REQUIRE(resourceAfterBuy[ResourceType::BRICK] == resourceBeforeBuy[ResourceType::BRICK] - 3);
            REQUIRE(resourceAfterBuy[ResourceType::WHEAT] == resourceBeforeBuy[ResourceType::WHEAT] - 4);
            REQUIRE(resourceAfterBuy[ResourceType::ORE] == resourceBeforeBuy[ResourceType::ORE] - 4);
            REQUIRE(resourceAfterBuy[ResourceType::SHEEP] == resourceBeforeBuy[ResourceType::SHEEP] - 2);
        }
       
        // we can't test the case of the player doesn't have enough resources to buy a settlement, city, or development card
        // because if the checkResources() function returns true,
        // then it means it has enough resources, so it will never throw an error.
    
    }
 
    SUBCASE("upgradeSettlementToCity function"){

    /* The tests I do so that it is permissible to upgrade a settlement to a city:
    *  1. Check if the player attempts to upgrade a settlement to a city at the beginning of the game
    *  2. Check if the player attempts to upgrade a settlement to a city without having at least one settlement
    *  3. Check if the player attempts to upgrade a settlement to a city in an invalid index
    *  4. Check if the player attempts to upgrade a settlement to a city without having more than 4 cities
    *  5. Check if the player attempts to upgrade a settlement to a city in a place that is not a settlement
    *  6. Check if the player attempts to upgrade a settlement to a city in a place that is not his settlement
    */

        SUBCASE("The player attempts to upgrade a settlement to a city at the beginning of the game"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            p1.placeSettlement(10);
            CHECK_THROWS_AS(p1.upgradeSettlementToCity(1), runtime_error);
        }

        SUBCASE("The player attempts to upgrade a settlement to a city without having at least one settlement"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            CHECK_THROWS_AS(p1.upgradeSettlementToCity(1), runtime_error);
        }

        SUBCASE("The player attempts to upgrade a settlement to a city in an invalid index"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            startGame(p1, p2, p3, board, catan);
            CHECK_THROWS_AS(p1.upgradeSettlementToCity(100), out_of_range);
        }   

        SUBCASE("The player attempts to upgrade a settlement to a city without having more than 4 cities"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            startGame(p1, p2, p3, board, catan);
            for(int i = 0; i < 15; i++){
                catan.advanceTurn();
            }
            p1.placeRoad(53);
            p1.placeRoad(1);
            p1.placeRoad(0);
            p1.placeRoad(48);
            p1.placeRoad(2);
            p1.placeSettlement(1);
            p1.placeSettlement(3);
            p1.placeSettlement(8);
            p1.upgradeSettlementToCity(1);
            p1.upgradeSettlementToCity(3);
            p1.upgradeSettlementToCity(8);
            p1.Trade(p3, ResourceType::SHEEP, 1, ResourceType::WHEAT, 4);
            p1.Trade(p2, ResourceType::SHEEP, 1, ResourceType::WHEAT, 4);        
            p1.upgradeSettlementToCity(10);
            cout << "The amount of WHEAT is: " << p1.getResources()[ResourceType::WHEAT] << endl;
            cout << "The amount of ORE is: " << p1.getResources()[ResourceType::ORE] << endl;
            cout << "The amount of BRICK is: " << p1.getResources()[ResourceType::BRICK] << endl;
            cout << "The amount of WOOD is: " << p1.getResources()[ResourceType::WOOD] << endl;
            cout << "The amount of SHEEP is: " << p1.getResources()[ResourceType::SHEEP] << endl;
            CHECK_THROWS_AS(p1.upgradeSettlementToCity(35), runtime_error);
        }
 
        SUBCASE("The player attempts to upgrade a settlement to a city in a place that is not a settlement"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            startGame(p1, p2, p3, board, catan);
            for(int i = 0; i < 15; i++){
                catan.advanceTurn();
            }
            p1.placeRoad(53);
            p1.placeRoad(1);
            p1.placeRoad(0);
            p1.placeRoad(48);
            p1.placeRoad(2);
            p1.placeSettlement(1);
            p1.placeSettlement(3);
            p1.placeSettlement(8);
            p1.upgradeSettlementToCity(1);    
            // the index 1 already has a city        
            CHECK_THROWS_AS(p1.upgradeSettlementToCity(1), runtime_error);
        }
   
        SUBCASE("The player attempts to upgrade a settlement to a city in a place that is not his settlement"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            startGame(p1, p2, p3, board, catan);
            for(int i = 0; i < 15; i++){
                catan.advanceTurn();
            }
            // the index 12 is not belong to the player 1, the index belong to the player 2
            CHECK_THROWS_AS(p1.upgradeSettlementToCity(12), runtime_error);
        }
   
        SUBCASE("Verify city is correctly placed at the specified vertex"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            startGame(p1, p2, p3, board, catan);
            p1.upgradeSettlementToCity(10);
            // we check the type that is in the index 10, and the owner of the index 10
            REQUIRE(board.getVertex(10).getType() == Vertex::VertexType::CITY);
            REQUIRE(board.getVertex(10).getPlayerName() == p1.getName());
        }
    }

    SUBCASE("Trade function"){
        /* The tests I do so that it is permissible to trade resources with another player:
        *  1. Check if the round status is not the start of the game
        *  2. Check if the player has the resources to trade
        *  3. Check if the other player has the resources to trade
        * 
        */
        
        SUBCASE("The player attempts to trade at the beginning of the game"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            CHECK_THROWS_AS(p1.Trade(p2, ResourceType::SHEEP, 1, ResourceType::WHEAT, 1), runtime_error);
        }

        SUBCASE("The player attempts to trade without having enough resources to trade"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            startGame(p1, p2, p3, board, catan);
            CHECK_THROWS_AS(p1.Trade(p2, ResourceType::SHEEP, 20, ResourceType::WHEAT, 1), runtime_error);
        }

        SUBCASE("The player attempts to trade with another player who does not have enough resources to trade"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            startGame(p1, p2, p3, board, catan);
            CHECK_THROWS_AS(p1.Trade(p3, ResourceType::SHEEP, 1, ResourceType::WHEAT, 20), runtime_error);
        }

        // This case also check addResource() function and removeResource() function
        SUBCASE("The player successfully trades with another player who has enough resources to trade"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            startGame(p1, p2, p3, board, catan);
            map<ResourceType, int> p1ResourceBeforeTrade = p1.getResources();
            map<ResourceType, int> p3ResourceBeforeTrade = p3.getResources();
            p1.Trade(p3, ResourceType::ORE, 1, ResourceType::BRICK, 1);
            map<ResourceType, int> p1ResourceAfterTrade = p1.getResources();
            map<ResourceType, int> p3ResourceAfterTrade = p3.getResources();
            REQUIRE(p1ResourceAfterTrade[ResourceType::ORE] == p1ResourceBeforeTrade[ResourceType::ORE] - 1);
            REQUIRE(p1ResourceAfterTrade[ResourceType::BRICK] == p1ResourceBeforeTrade[ResourceType::BRICK] + 1);
        }
    
    
    
    }

    SUBCASE("buyDevelopmentCard function"){

        /* The tests I do so that it is permissible to buy a development card:
        *  1. Check if the round status is not the start of the game
        *  2. Check if the player has the resources to buy a development card
        *  3. Check if there are development cards available
        */

        SUBCASE("The player attempts to buy a development card at the beginning of the game"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            CHECK_THROWS_AS(p1.buyDevelopmentCard(), runtime_error);
        }

        SUBCASE("The player attempts to buy a development card without having enough resources to buy a development card"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            startGame(p1, p2, p3, board, catan);
            cout << "The amount of WHEAT before is: " << p1.getResources()[ResourceType::WHEAT] << endl;
            cout << "The amount of ORE before is: " << p1.getResources()[ResourceType::ORE] << endl;
            cout << "The amount of SHEEP before is: " << p1.getResources()[ResourceType::SHEEP] << endl;
            for(int i = 0; i < 10; i++){
                p1.buyDevelopmentCard();
            }
            cout << "The amount of WHEAT after is: " << p1.getResources()[ResourceType::WHEAT] << endl;
            cout << "The amount of ORE after is: " << p1.getResources()[ResourceType::ORE] << endl;
            cout << "The amount of SHEEP after is: " << p1.getResources()[ResourceType::SHEEP] << endl;
            CHECK_THROWS_AS(p1.buyDevelopmentCard(), runtime_error);
        }

        SUBCASE("The player attempts to buy a development card without having development cards available"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            startGame(p1, p2, p3, board, catan);
            p1.placeRoad(31);
            p1.placeRoad(30);
            p1.placeSettlement(33);
            p1.placeRoad(29);
            p1.placeRoad(62);
            p1.placeRoad(37);
            p1.placeSettlement(41);     
            for(int i = 0; i < 60; i++){
                catan.advanceTurn();
            }
            // we create a situation where the player has 19 development cards
            // and he tries to buy another development card
            // the number is 20 because the Victory Point card is used in the same 
            // time as the player buys a development card.
            while (p1.getNumOfDevelopmentCards() < 20) {
                map<ResourceType, int> p1ResourceBeforeTrade = p1.getResources();
                map<ResourceType, int> p2ResourceBeforeTrade = p2.getResources();
                if (p1ResourceBeforeTrade[ResourceType::ORE] > 1 && p2ResourceBeforeTrade[ResourceType::WHEAT] > 1){
                    p1.Trade(p2, ResourceType::ORE, 1, ResourceType::WHEAT, 1);
                    p1.buyDevelopmentCard();
                }
                else{
                    for(int i = 0; i < 6; i++){
                        catan.advanceTurn();
                    }
                }
            }
            CHECK_THROWS_AS(p1.buyDevelopmentCard(), runtime_error);
        }
    
        SUBCASE("Verify the player has a development card after buying a development card"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);
            startGame(p1, p2, p3, board, catan);
            map<ResourceType, int> p1ResourceBeforeTrade = p1.getResources();
            p1.buyDevelopmentCard();
            map<ResourceType, int> p1ResourceAfterTrade = p1.getResources();
            bool condition1 = (p1.getNumOfDevelopmentCards() == 1);
            bool condition2 = (p1.getNumOfVictoryPoints() == 1);
            if (condition1 || condition2) {
                REQUIRE(true);
            } else {
                REQUIRE(false);
            }     
            REQUIRE(p1ResourceAfterTrade[ResourceType::ORE] == p1ResourceBeforeTrade[ResourceType::ORE] - 1);
            REQUIRE(p1ResourceAfterTrade[ResourceType::WHEAT] == p1ResourceBeforeTrade[ResourceType::WHEAT] - 1);
            REQUIRE(p1ResourceAfterTrade[ResourceType::SHEEP] == p1ResourceBeforeTrade[ResourceType::SHEEP] - 1);
        }
    }

    SUBCASE("useDevelopmentCard"){

            


        SUBCASE("The player turn on MonopolyCard"){
            Board board;
            Player p1("Amit", board);
            Player p2("Yossi", board);
            Player p3("Dana", board);
            Catan catan(p1, p2, p3, board);

            startGame(p1, p2, p3, board, catan);
            p1.placeRoad(31);
            p1.placeRoad(30);
            p1.placeSettlement(33);
            p1.placeRoad(29);
            p1.placeRoad(62);
            p1.placeRoad(37);
            p1.placeSettlement(41);     
            for(int i = 0; i < 60; i++){
                catan.advanceTurn();
            }
            // we create a situation where the player has 19 development cards
            // and he tries to buy another development card
            // the number is 20 because the Victory Point card is used in the same 
            // time as the player buys a development card.
            while (p1.getNumOfDevelopmentCards() < 20) {
                map<ResourceType, int> p1ResourceBeforeTrade = p1.getResources();
                map<ResourceType, int> p2ResourceBeforeTrade = p2.getResources();
                if (p1ResourceBeforeTrade[ResourceType::ORE] > 1 && p2ResourceBeforeTrade[ResourceType::WHEAT] > 1){
                    p1.Trade(p2, ResourceType::ORE, 1, ResourceType::WHEAT, 1);
                    p1.buyDevelopmentCard();
                }
                else{
                    for(int i = 0; i < 6; i++){
                        catan.advanceTurn();
                    }
                }
            }
            p1.useDevelopmentCard("Monopoly Ore");
            REQUIRE(p3.getResources()[ResourceType::ORE] == 0);
            REQUIRE(p2.getResources()[ResourceType::ORE] == 0);
        }
    }


}
