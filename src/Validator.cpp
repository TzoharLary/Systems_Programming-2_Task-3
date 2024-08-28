#include "Validator.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Road.hpp"
#include "Tile.hpp"
#include "Vertex.hpp"
#include <iostream>
#include <stdexcept>
#include <exception>
using std::vector;
using std::map;
using std::cout;
using std::endl;
using std::out_of_range;
using std::runtime_error;
using std::exception;
using std::cerr;
using std::to_string;





Validator::Validator(const string& className,
    const string& functionName,
    void* obj,
    int index, 
    Board& board,
    ResourceType giveResource, 
    int giveAmount, 
    ResourceType takeResource, 
    int takeAmount,
    Player* otherPlayer)
    : className(className),
    functionName(functionName),
    obj(obj), 
    index(index),
    board(board), 
    giveResource(giveResource),
    giveAmount(giveAmount),
    takeResource(takeResource), 
    takeAmount(takeAmount),
    otherPlayer(otherPlayer) {
    validate();
}


/* This method is responsible for validating objects based on their class type.
 * 
 * The `validate()` method dynamically checks the class name 
 * stored in the `className` member
 * and calls the appropriate validation method for that class. 
 * 
 * If a validation method throws an exception, the exception is 
 * caught, and the `valid` flag is set to false, 
 * indicating that the validation has failed.
 * 
 * This method provides a flexible and extendable mechanism to validate different objects
 * within the application, making it easier to maintain and scale the validation logic as new classes are added.
 * 
 * The structure of this method allows it to be easily expanded in the future to handle additional classes
 * by adding more `else if` blocks or similar constructs. 
 */
void Validator::validate() {
    try
    {        
        if (className == "Player") {
            validatePlayer();
        } 
        /*
        else if (className == "Board") {
            validateBoard();
        } else if (className == "Road") {
            validateRoad();
        } else if (className == "Tile") {
            validateTile();
        } else if (className == "Vertex") {
            validateVertex();
        }
        */
    
        // Add more classes as needed
    }
    catch(const exception& e)
    {
        cerr << e.what() << endl;
        valid = false;   
    }
}

bool Validator::isValid() const {
    return valid;
}

void Validator::validatePlayer() {
    Player* player = static_cast<Player*>(obj);
    Board& boardRef = board;
    valid = true;
    // validate player turn, and alowed to trade in any turn
    if(player->isMyTurn == false && functionName != "Trade") {
        valid = false;
        cout << "The player: " << player->getName() << " Try to do an action but it is not his turn" << endl;
        throw runtime_error("It is not your turn.");
    }

    /* The tests I do so that it is permissible to assume a settlement in the desired index:
    *  1. Check if the player has more than 5 settlements
    *  2. Check if the vertexIndex is found in the vector and exists
    *  3. Check if there is a settlement on an adjacent vertex
    *  4. Check if there is a settlement on the vertex
    *  
    */
    if (functionName == "placeSettlement") {
        // Check if the player has more than 5 settlements
        if (player->getNumOfSettlements() >= 5) {
            valid = false;
            throw runtime_error("Player cannot have more than 5 settlements.");
        }
         // Check if the vertexIndex is found in the vector and exists
        if (index < 0 || index >= static_cast<int>(boardRef.vertices.size())) {
            valid = false;
            throw out_of_range("Invalid vertex index when trying to place a settlement");
        }

        Vertex& vertex = boardRef.vertices.at(index);
        if (vertex.isOccupied()) {
            valid = false;
            throw runtime_error("There is already a settlement on this vertex. (vertex index: " + to_string(index) + ")");
        }
        /*   Check if there is a settlement on an adjacent vertex
         Do it using for loop that iterates over the adjacent vertices of the current vertex
         and checks if there is a settlement on any of them
        */ 
        for (int adjacentVertex : vertex.getAdjacentVertices()) {
            if (boardRef.vertices.at(adjacentVertex).isOccupied()) { 
                valid = false;
                throw runtime_error("There is a settlement on an adjacent vertex");
            }
        }
   
   } else if (functionName == "placeRoad") {
        // Check if the index is valid and in the range of the roads vector
        if (index < 0 || index >= 72) {
            valid = false;
            throw out_of_range("Invalid road index");
        }

        
        Road& road = boardRef.roads.at(index);
        // Check if the road is already occupied
        if (road.isOccupied()) {
            valid = false;
            throw runtime_error("The road is already occupied by " + road.getPlayerName());
        }
        // Check if the player has any settlements
        if (player->getNumOfSettlements() < 0) {
            valid = false;
            throw runtime_error("You must have at least one settlement to build a road.");
        }
        // if condition to check if the road is near a settlement that belongs to the player
        bool hasPlayerSettlement = false;
        for (int vertexIndex : road.getBetweenVertices()) {
            Vertex& vertex = boardRef.vertices.at(vertexIndex);
            if (vertex.getPlayerName() == player->getName()) {
                hasPlayerSettlement = true;
                break;
            }
        }
       
        // if condition to check if the road is near another road that belongs to the player
        bool hasToadNearRoad = false;
        for (int roadIndex : road.getAdjacentRoads()) {
            Road& adjacentRoad = boardRef.roads.at(roadIndex);
            if (adjacentRoad.isOccupied() && adjacentRoad.getPlayerName() == player->getName()) {
                hasToadNearRoad = true;
                break;
            }
        }
        if (!hasPlayerSettlement && !hasToadNearRoad) {
            cout << "the road: " << road.getId() << " has no settlement or road near it" << endl;
            valid = false;
            throw runtime_error("You must build a road near one of your settlements or near one of your roads.");
        }
        

    } else if (functionName == "upgradeSettlementToCity") {

        // check if this is the start of the game the player cannot trade
        if (player->afterStartGame == false) {
            valid = false;
            throw runtime_error("You cannot upgrade a settlement to a city at the beginning of the game.");
        }

        if (player->getNumOfSettlements() < 0) {
            valid = false;
            throw runtime_error("You must have at least one settlement to upgrade to a city.");
        }

        if (index < 0 || index >= static_cast<int>(boardRef.vertices.size()))  {
            valid = false;
            throw out_of_range("Invalid vertex index when trying to place a settlement");
        }
       
        if (player->getNumOfCity() >= 4) {
            valid = false;
            throw runtime_error("You cannot have more than 4 cities.");
        }

        Vertex& vertex = boardRef.vertices.at(index);

        if ( vertex.getType() != Vertex::VertexType::SETTLEMENT){
            valid = false;
            throw runtime_error("You can only upgrade settlements to cities.");
        
        }
      
        if ( vertex.getPlayerName() != player->getName()) {
            valid = false;
            throw runtime_error("You can only upgrade your own settlements to cities.");
        }
        
    }  
    else if (functionName == "Trade"){
        // check if this is the start of the game the player cannot trade
        if (player->afterStartGame == false) {
            valid = false;
            throw runtime_error("You cannot trade at the beginning of the game.");
        }
        // check if the player has the resources to trade
        if (giveAmount > 0 && !player->checkResources({ {giveResource, giveAmount} })) {
            valid = false;
            throw runtime_error("You dont have enough resources to trade");
        }

        //  check if the other player has the resources to trade
        if (otherPlayer != nullptr && takeAmount > 0 && !otherPlayer->checkResources({ {takeResource, takeAmount} })) {
            valid = false;
            throw runtime_error("The player you want to trade with doesn't have enough resources");
        }
    }
    else if (functionName == "buyDevelopmentCard") {
            // check if this is the start of the game the player cannot trade
            if (player->afterStartGame == false) {
            valid = false;
            throw runtime_error("You cannot buy a development card at the beginning of the game.");
            }

            // check if the player has the resources to buy a development card
            if (!player->checkResources({{ResourceType::WHEAT, 1}, {ResourceType::SHEEP, 1}, {ResourceType::ORE, 1}})) {
                throw runtime_error("You don't have enough resources to buy a development card.");
            }

            // check if there are development cards available
            if (board.getDeck().empty()) {
                throw runtime_error("You cannot buy a development card because there are no cards left in the deck.");
            }
        }  
    else if (functionName == "useDevelopmentCard") {
        // Check if the card was not purchased this turn.
        if (player->parchaseDevelopmentCardThisTurn == true) {
            valid = false;
            throw runtime_error("You cannot use a development card that was purchased this turn.");
        }
    }
}

/*
void Validator::validateBoard() {
    Board* board = static_cast<Board*>(obj);
    // Add Board specific validations
}

void Validator::validateRoad() {
    Road* road = static_cast<Road*>(obj);
    // Add Road specific validations
}

void Validator::validateTile() {
    Tile* tile = static_cast<Tile*>(obj);
    // Add Tile specific validations
}

void Validator::validateVertex() {
    Vertex* vertex = static_cast<Vertex*>(obj);
    // Add Vertex specific validations
}
*/
