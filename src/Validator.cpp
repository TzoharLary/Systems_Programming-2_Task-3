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




Validator::Validator(const string& className, const string& functionName, void* obj, int index,  Board& board)
    : className(className), functionName(functionName), obj(obj), index(index), board(board) {
    validate();
}

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
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
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

    if (functionName == "placeSettlement") {
        // Check if the player has more than 5 settlements
        if (player->settlements.size() >= 5) {
            valid = false;
            throw std::runtime_error("Player cannot have more than 5 settlements.");
        }
         // Check if the vertexIndex is found in the vertor and exists
        if (index < 0 || index >= static_cast<int>(boardRef.vertices.size())) {
            valid = false;
            throw std::out_of_range("Invalid vertex index when trying to place a settlement");
        }


        Vertex& vertex = boardRef.vertices.at(index);
        if (vertex.occupied) {
            valid = false;
            throw std::runtime_error("There is already a settlement on this vertex");
        }
        /*   Check if there is a settlement on an adjacent vertex
         For loop that iterates over the adjacent vertices of the current vertex
         and checks if there is a settlement on any of them
        */ 
        for (int adjacentVertex : vertex.adjacentVertices) {
            if (boardRef.vertices.at(adjacentVertex).occupied) { 
                valid = false;
                throw std::runtime_error("There is a settlement on an adjacent vertex");
            }
        }
   
   } else if (functionName == "placeRoad") {
        // Check if the index is valid and in the range of the roads vector
        if (index < 0 || index >= 72) {
            valid = false;
            throw std::out_of_range("Invalid road index");
        }

        Road& road = boardRef.roads.at(index);
        // Check if the road is already occupied
        if (road.isOccupied()) {
            valid = false;
            throw std::runtime_error("The road is already occupied by " + road.getPlayerName());
        }
        if (player->settlements.size() < 0) {
            valid = false;
            throw std::runtime_error("You must have at least one settlement to build a road.");
        }
        // until here all check and work
        // TODO: add adjacent roads check for valid built road

        // if condition to check if the road is near a settlement that belongs to the player
        for (int vertexIndex : road.getBetweenVertices()) {
            Vertex& vertex = boardRef.vertices.at(vertexIndex);
            if (vertex.occupied && vertex.getPlayerName() == player->getName()) {
                break;
            }
        }
        /*
        
        */
        if (!valid) {
            valid = false;
            throw std::runtime_error("You can only build a road near your own settlements.");
        }
        

    } else if (functionName == "upgradeSettlementToCity") {
        if (index < 0 || index >= static_cast<int>(boardRef.vertices.size()))  {
            valid = false;
            throw std::out_of_range("Invalid vertex index when trying to place a settlement");
        }

        if (player->Citys.size() >= 4) {
            valid = false;
            throw std::runtime_error("You cannot have more than 4 cities.");
        }

        Vertex& vertex = boardRef.vertices.at(index);

        if (!vertex.occupied || vertex.player != player || vertex.getType() == Vertex::VertexType::SETTLEMENT) {
            valid = false;
            throw std::runtime_error("You can only upgrade your own settlements to cities.");
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
