#include "Player.hpp"
#include "Board.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>
using std::cout;
using std::endl;
using std::find;


Player::Player(const std::string &name) : name(name), points(0) {
    for (int i = WOOD; i <= ORE; ++i) {
        resources[static_cast<ResourceType>(i)] = 0;
    }
}

void Player::Buy(BuyType type) {
    // There is no problem creating a map with each call
    // to the function because the local object cost is created
    // on the stack and automatically deleted at the end of the function.
    std::map<ResourceType, int> cost;

    switch (type) {
        case ROAD:
            cost = {{WOOD, 1}, {BRICK, 1}};
            break;
        case SETTLEMENTS:
            cost = {{WOOD, 1}, {BRICK, 1}, {SHEEP, 1}, {WHEAT, 1}};
            break;
        case CITY:
            cost = {{WHEAT, 2}, {ORE, 3}};
            break;
        case DEVELOPMENT_CARD:
            cost = {{ORE, 1}, {WHEAT, 1}, {SHEEP, 1}};
            break;
        default:
            std::cout << "Unknown purchase type." << std::endl;
            return;
    }

    if (checkResources(cost)) {
        // Deduct resources using removeResource
        try {
            for (const auto& item : cost) {
                removeResource(item.first, item.second);
            }
            cout << "Purchase successful!" << endl;
        } catch (const std::runtime_error& e) {
            cout << e.what() << endl;
        }
    }
    else {
        cout << "Not enough resources to complete the purchase." << endl;
    }
}

bool Player::checkResources(const std::map<ResourceType, int>& cost) {
    bool hasAllResources = true;
    std::cout << "Missing resources:" << std::endl;

    for (const auto& item : cost) {
        if (resources[item.first] < item.second) {
            hasAllResources = false;
            std::cout << "Resource: " << item.first << ", Required: " << item.second << ", Available: " << resources[item.first] << std::endl;
        }
    }

    return hasAllResources;
}

void Player::placeSettlement(int vertexIndex, Board& board) {
    
    // Check if the vertexIndex is found in the map and exists
    if (board.vertices.find(vertexIndex) == board.vertices.end()) {
        throw std::out_of_range("Invalid vertex index");
    }

    // Check if the player has more than 5 settlements
    if (settlements.size() >= 5) {
        throw std::runtime_error("You cannot have more than 5 settlements.");
    }

    // Get the vertex object from the map
    Vertex& vertex = board.vertices.at(vertexIndex); // Using at() instead of []

    // check if the vertex is occupied by another player
    if (vertex.occupied) {
        throw std::runtime_error("There is already a settlement on this vertex");
    }

    /*   Check if there is a settlement on an adjacent vertex
         For loop that iterates over the adjacent vertices of the current vertex
         and checks if there is a settlement on any of them
    */ 
    for (int adjacentVertex : vertex.adjacentVertices) {
        if (board.vertices.at(adjacentVertex).occupied) { 
            throw std::runtime_error("There is a settlement on an adjacent vertex");
        }
    }

    Buy(SETTLEMENTS);

    vertex.occupied = true; // From now the vertex will be occupied by the player
    vertex.player = this; // Save the pointer to the player
    vertex.setType(SETTLEMENT); // Set the type of the vertex to a settlement
    this->settlements.push_back(vertexIndex); // Add the settlement to the player's list of settlements
    points += 1; // Settlement is worth 1 point

}

void Player::placeRoad(int roadIndex, Board& board) {
    // bool variable for know later if the index of the road is valid
    bool validRoad = false;

    if (roadIndex < 0 || roadIndex >= 72) {
    throw std::out_of_range("Invalid road index");
    }

    //  if (std::find(board.roads.begin(), board.roads.end(), roadIndex) != board.roads.end()) {
    //     // throw std::out_of_range("the problem is here");
    //  }
 
    Road& road = board.roads.at(roadIndex);

    if (road.player != nullptr) {
        throw std::runtime_error("This road is already occupied by another player");
    }
    // TODO: add adjacent roads check for valid built road

    if(this.getPoints > 2){
        Buy(ROAD);
    }
    
    road.setPlayer(this);

    validRoad = true;

    if (!validRoad) {
        cout << "the road is not valid" << endl;
        throw std::out_of_range("Invalid road index");
    }

    cout << name << " placed a road on road " << roadIndex << endl;
}

void Player::upgradeSettlementToCity(int vertexIndex, Board& board) {
    // Check if the specified vertex index exists in the board's vertices map
    if (board.vertices.find(vertexIndex) == board.vertices.end()) {
        // If the vertex index does not exist, throw an out_of_range exception
        throw std::out_of_range("Invalid vertex index");
    }

    // Check if the player has more than 5 settlements
    if (Citys.size() >= 4) {
        throw std::runtime_error("You cannot have more than 5 settlements.");
    }
    
    // Access the vertex by index, assuming existence is already verified
    Vertex& vertex = board.vertices.at(vertexIndex);

    // Check if the vertex is not occupied, if it's not owned by the current player, or if it's not a settlement
    if (!vertex.occupied || vertex.player != this || vertex.type != SETTLEMENT) {
        // If any condition is true, throw a runtime_error indicating the action cannot be performed
        throw std::runtime_error("You can only upgrade your own settlements to cities.");
    }

    // try to buy
    Buy(CITY);
    // Change the vertex type to CITY, indicating an upgrade
    vertex.setType(CITY);
    // Increment points by 1. This assumes a settlement is worth 1 point and upgrading to a city makes it worth 2 points in total
    points += 1;

    // Output a message indicating the player has upgraded a settlement to a city at the specified vertex
    std::cout << "Player " << name << " upgraded a settlement to a city on vertex " << vertexIndex << std::endl;
}

void Player::addResource(ResourceType resource, int amount) {
    resources[resource] += amount; 
}

void Player::removeResource(ResourceType resource, int amount) {
    if (resources[resource] >= amount) {
        resources[resource] -= amount;
        if (resources[resource] == 0) {
            resources.erase(resource);
        }
    } else {
        throw std::runtime_error("Not enough resources");
    }
}

std::string Player::getName() const {
    return name;
}

int Player::getPoints() const {
    return points;
}
