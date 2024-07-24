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




Validator::Validator(const string& className, const string& functionName, void* obj, int index, void* board)
    : className(className), functionName(functionName), obj(obj), index(index), board(board) {
    validate();
}

void Validator::validate() {
    if (className == "Player") {
        validatePlayer();
    } else if (className == "Board") {
        validateBoard();
    } else if (className == "Road") {
        validateRoad();
    } else if (className == "Tile") {
        validateTile();
    } else if (className == "Vertex") {
        validateVertex();
    }
    // Add more classes as needed
}

void Validator::validatePlayer() {
    Player* player = static_cast<Player*>(obj);
    Board* boardPtr = static_cast<Board*>(board);

    if (functionName == "placeSettlement") {
        if (player->settlements.size() >= 5) {
            throw std::runtime_error("Player cannot have more than 5 settlements.");
        }

        if (boardPtr->vertices.find(index) == boardPtr->vertices.end()) {
            throw std::out_of_range("Invalid vertex index");
        }

        Vertex& vertex = boardPtr->vertices.at(index);
        if (vertex.occupied) {
            throw std::runtime_error("There is already a settlement on this vertex");
        }

        for (int adjacentVertex : vertex.adjacentVertices) {
            if (boardPtr->vertices.at(adjacentVertex).occupied) { 
                throw std::runtime_error("There is a settlement on an adjacent vertex");
            }
        }
    } else if (functionName == "placeRoad") {
        if (index < 0 || index >= 72) {
            throw std::out_of_range("Invalid road index");
        }

        Road& road = boardPtr->roads.at(index);

        bool validRoad = true; // יש לקבוע validRoad לפי הקונטקסט שלך

        if (!validRoad) {
            std::cout << "the road is not valid" << std::endl;
            throw std::out_of_range("Invalid road index");
        }
    } else if (functionName == "upgradeSettlementToCity") {
        if (boardPtr->vertices.find(index) == boardPtr->vertices.end()) {
            throw std::out_of_range("Invalid vertex index");
        }

        if (player->Citys.size() >= 4) {
            throw std::runtime_error("You cannot have more than 4 cities.");
        }

        Vertex& vertex = boardPtr->vertices.at(index);

        if (!vertex.occupied || vertex.player != player || vertex.getType() == Vertex::VertexType::SETTLEMENT) {
            throw std::runtime_error("You can only upgrade your own settlements to cities.");
        }
    }
}

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
