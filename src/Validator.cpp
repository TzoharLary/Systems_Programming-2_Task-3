#include "Validator.hpp"
#include "Player.hpp"
#include "catan.hpp"
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
    /* Explanation of the try-catch block:
    *  The try block is used to enclose the validation logic for the different classes.
    *  If an exception is thrown during the validation process, it is caught in the catch block.
    *  The catch block sets the `valid` flag to false, indicating that the validation has failed.
    *  
    */
    try{        
        if (className == "Player") {
            validatePlayer();
        } 
    
    }
    catch(const exception& e){
        cerr << e.what() << endl;
        valid = false;  
        #ifdef RUNNING_TESTS
            throw;  // rethrow the exception for testing purposes
        #else
            handleError(e);  // handle the error in the normal program flow
            
        #endif 
    }
}

bool Validator::isValid() const {
    return valid;
}
void Validator::handleError(const std::exception& e) {
        // handle the error in the normal program flow
        std::cerr << "Handled error: " << e.what() << std::endl;
}
void Validator::validatePlayer() {
    Player* player = static_cast<Player*>(obj);
    Board& boardRef = board;
    valid = true;
    // validate player turn, and alowed to trade in any turn
    if(player->isMyTurn == false && functionName != "Trade") {
        cout << "The player: " << player->getName() << " Try to do an action but it is not his turn" << endl;
        throw runtime_error("It is not your turn.");
    }

    /* The tests I do so that it is permissible to assume a settlement in the desired index:
    *  1. Check if the player has more than 5 settlements
    *  2. Check if the vertexIndex is found in the vector and exists
    *  3. Check if there is a settlement on an adjacent vertex
    *  4. Check if there is a settlement on the vertex
    *  5. Check if it's the start of the game, during the first round, and the player is attempting to build more that 1 settlement in this turn
    *  6. Check if it's the start of the game, during the second round, and the player is attempting to build more that 1 settlement in this turn
    *  7. Check if the round is after the second, and the index is near a 2 adjacent roads
    */
    if (functionName == "placeSettlement") {

        // Check if the player has more than 5 settlements
        if (player->getNumOfSettlements() >= 5) {
            throw runtime_error("Player cannot have more than 5 settlements.");
        }
         // Check if the vertexIndex is found in the vector and exists
        if (index < 0 || index >= static_cast<int>(boardRef.vertices.size())) {
            throw out_of_range("Invalid vertex index when trying to place a settlement");
        }
        Vertex& vertex = boardRef.vertices.at(index);
        if (vertex.isOccupied()) {
            throw runtime_error("There is already a settlement on this vertex. (vertex index: " + to_string(index) + ")");
        }
        /*   Check if there is a settlement on an adjacent vertex
         Do it using for loop that iterates over the adjacent vertices of the current vertex
         and checks if there is a settlement on any of them
        */ 
        for (int adjacentVertex : vertex.getAdjacentVertices()) {
            if (boardRef.vertices.at(adjacentVertex).isOccupied()) { 
                throw runtime_error("There is a settlement on an adjacent vertex");
            }
        }
           // Check if it's the start of the game, during the first round, and the player is attempting to build more that 1 settlement in this turn
        if (player->getRoundStatus()[0] && player->getNumOfSettlements() == 1) {
            throw runtime_error("You cannot place more than 1 settlement at the first round of the game.");
        }
        // Check if it's the start of the game, during the second round, and the player is attempting to build more that 1 settlement in this turn
        if(player->getRoundStatus()[1] && player->getNumOfSettlements() == 2) {
            throw runtime_error("You cannot place more than 1 settlement at the second round of the game.");
        }
        // Check if the player want to build a settlement on a vertex that is not near any of his roads
        if (player->getRoundStatus()[2]) {
            // Get the roads that are on the vertex that the player wants to build a settlement on.
            vector<const Road*> roadsOnVertex = boardRef.getRoadsOnVertex(index);
            // Check for each road whether it belongs to the player who is building.
            for (const Road* road : roadsOnVertex) {
                // Check if the road is occupied by the player who is building.
                if (road->isOccupied() && road->getPlayerName() == player->getName()) {  
                    return;
                }
            }
            // If no valid adjacent road is found, throw an exception or handle it accordingly
            throw runtime_error("Player cannot build: the player does not have a road connected to the vertex.");
        }
   } 
   /* The tests I do so that it is permissible to assume a road in the desired index:
    *  1. Check if the index is valid and in the range of the roads vector
    *  2. Check if the road is already occupied
    *  3. Check if the road is near a settlement that belongs to the player
    *  4. Check if the road is near another road that belongs to the player
   */
   else if (functionName == "placeRoad") {
        // Check if the index is valid and in the range of the roads vector
        if (index < 0 || index >= 72) {
            throw out_of_range("Invalid road index");
        }
        Road& road = boardRef.roads.at(index);
        // Check if the road is already occupied
        if (road.isOccupied()) {
            throw runtime_error("The road is already occupied by " + road.getPlayerName());
        }
   
        // if condition to check if the road is near a settlement that belongs to the player after the second round
        bool roundIsRegular = player->getRoundStatus()[2];
        bool hasPlayerSettlement = false;
        for (int vertexIndex : road.getBetweenVertices()) {
            Vertex& vertex = boardRef.vertices.at(vertexIndex);
            if (vertex.getPlayerName() == player->getName()) {
                hasPlayerSettlement = true;
                break;
            }
        }
       
        // if condition to check if the road is near another road that belongs to the player
        bool hasRoadNearRoad = false;
        for (int roadIndex : road.getAdjacentRoads()) {
            Road& adjacentRoad = boardRef.roads.at(roadIndex);
            if (adjacentRoad.isOccupied() && adjacentRoad.getPlayerName() == player->getName()) {
                hasRoadNearRoad = true;
                break;
            }
        }
   

        if (roundIsRegular && !hasPlayerSettlement && !hasRoadNearRoad) {
            cout << "the road: " << road.getId() << " has no settlement or road near it" << endl;
            throw runtime_error("You must build a road near one of your settlements or near one of your roads.");
        }
        

    } 
    /* The tests I do so that it is permissible to upgrade a settlement to a city:
    *  1. Check if the player has at least one settlement
    *  2. Check if the index is valid and in the range of the vertices vector
    *  3. Check if the player has more than 4 cities
    *  4. Check if the vertex is a settlement
    *  5. Check if the settlement belongs to the player
    *  6. Check if the player has the resources to trade
    */
    else if (functionName == "upgradeSettlementToCity") {

        // check if this is the start of the game the player cannot trade
        if (!player->getRoundStatus()[2]) {
            throw runtime_error("You cannot upgrade a settlement to a city at the beginning of the game.");
        }

        if (player->getNumOfSettlements() < 0) {
            throw runtime_error("You must have at least one settlement to upgrade to a city.");
        }

        if (index < 0 || index >= static_cast<int>(boardRef.vertices.size()))  {
            throw out_of_range("Invalid vertex index when trying to place a settlement");
        }
       
        if (player->getNumOfCity() >= 4) {
            throw runtime_error("You cannot have more than 4 cities.");
        }

        Vertex& vertex = boardRef.vertices.at(index);

        if ( vertex.getType() != Vertex::VertexType::SETTLEMENT){
            throw runtime_error("You can only upgrade settlements to cities.");
        
        }
      
        if ( vertex.getPlayerName() != player->getName()) {
            throw runtime_error("You can only upgrade your own settlements to cities.");
        }
        
    }  
    /* The tests I do so that it is permissible to trade resources with another player:
    *  1. Check if the round status is not the start of the game
    *  2. Check if the player has the resources to trade
    *  3. Check if the other player has the resources to trade
    * 
    */
    else if (functionName == "Trade"){
        // check if this is the start of the game the player cannot trade
        if (!player->getRoundStatus()[2]) {
            throw runtime_error("You cannot trade at the beginning of the game.");
        }
        // check if the player has the resources to trade
        if (giveAmount > 0 && !player->checkResources({ {giveResource, giveAmount} })) {
            throw runtime_error("You dont have enough resources to trade");
        }

        //  check if the other player has the resources to trade
        if (otherPlayer != nullptr && takeAmount > 0 && !otherPlayer->checkResources({ {takeResource, takeAmount} })) {
            throw runtime_error("The player you want to trade with doesn't have enough resources");
        }
    }
    /* The tests I do so that it is permissible to buy a development card:
    *  1. Check if the round status is not the start of the game
    *  2. Check if the player has the resources to buy a development card
    *  3. Check if there are development cards available
    */
    else if (functionName == "buyDevelopmentCard") {
            // check if this is the start of the game the player cannot trade
            if (!player->getRoundStatus()[2]) {
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

    /* The tests I do so that it is permissible to use a development card:
    *  1. Check if the player has the card in his hand.
    *  2. Check if the card was purchased this turn, and he not victory point ot Year of Plenty
    */
    else if (functionName == "useDevelopmentCard") {
        
        // Check if the player has the card in his hand.
        if (player->getNumOfDevelopmentCards() == 0) {
            throw runtime_error("You don't have any development cards to use.");
        }
       

    }
}


