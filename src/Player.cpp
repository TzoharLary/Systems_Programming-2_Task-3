#include "Player.hpp"
#include "Board.hpp"
#include <stdexcept>
#include <iostream>
using std::cout;
using std::endl;


Player::Player(const std::string &name) : name(name), points(0) {}


void Player::placeSettlement(int vertexIndex, Board& board) {

    printf("vertexIndex: %d\n", vertexIndex);
   
    // Check if the vertexIndex is found in the map and exists
    if (board.vertices.find(vertexIndex) == board.vertices.end()) {
        throw std::out_of_range("Invalid vertex index");
    }
    printf("after first if\n");

    // Check if the player has more than 5 settlements
    if (settlements.size() >= 5) {
        throw std::runtime_error("You cannot have more than 5 settlements.");
    }
    printf("after second if\n");

    // Get the vertex object from the map
    Vertex& vertex = board.vertices.at(vertexIndex); // Using at() instead of []

    printf("after define vertex to board.vertices.at(vertexIndex)\n");

    // check if the vertex is occupied by another player
    if (vertex.occupied) {
        throw std::runtime_error("There is already a settlement on this vertex");
    }

    printf("after third if\n");

    // Check if there is a settlement on an adjacent vertex
    // For loop that iterates over the adjacent vertices of the current vertex
    // and checks if there is a settlement on any of them
    for (int adjacentVertex : vertex.adjacentVertices) {
        printf("adjacentVertex: %d\n", adjacentVertex);
        printf("adjacentVertex.type: %d\n", board.vertices.at(adjacentVertex).type);
        if (board.vertices.at(adjacentVertex).occupied) { // Using at() instead of []
            throw std::runtime_error("There is a settlement on an adjacent vertex");
        }

    }

    vertex.occupied = true; // From now the vertex will be occupied by the player
    vertex.player = this; // Save the pointer to the player
    vertex.type = SETTLEMENT; // Set the type of the vertex to a settlement
    this->settlements.push_back(vertexIndex); // Add the settlement to the player's list of settlements
    cout << "Player " << name << " placed a settlement on vertex " << vertexIndex << endl;
    points += 1; // Settlement is worth 1 point

}



void Player::placeRoad(int roadIndex, Board& board) {

    cout << "roadIndex: " << roadIndex << endl;
    bool validRoad = false;

    if (roadIndex < 0 || roadIndex >= 72) {
    throw std::out_of_range("Invalid road index");
    }

    cout << "after first if" << endl;


    Road& road = board.roads[roadIndex];

    cout << "after define road to board.roads[roadIndex]" << endl;
    
    if (road.player != nullptr) {
        throw std::runtime_error("This road is already occupied by another player");
    }

    cout << "after second if" << endl;

    road.player = this;

    cout << "after road.player = this" << endl;
    
    if (!validRoad) {
        cout << "the road is not valid" << endl;
        throw std::out_of_range("Invalid road index");
    }

    cout << "after third if" << endl;

    std::cout << "Player " << name << " placed a road on road " << roadIndex << std::endl;
}


void Player::upgradeSettlementToCity(int vertexIndex, Board& board) {
    if (board.vertices.find(vertexIndex) == board.vertices.end()) {
        throw std::out_of_range("Invalid vertex index");
    }

    Vertex& vertex = board.vertices.at(vertexIndex);

    if (!vertex.occupied || vertex.player != this || vertex.type != SETTLEMENT) {
        throw std::runtime_error("You can only upgrade your own settlements to cities.");
    }

    vertex.type = CITY;
    points += 1; // City is worth 2 points, and we already counted 1 for the settlement

    std::cout << "Player " << name << " upgraded a settlement to a city on vertex " << vertexIndex << std::endl;
}

void Player::addResource(ResourceType resource, int amount) {
    resources[resource] += amount; // הוספת כמות למשאב
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
