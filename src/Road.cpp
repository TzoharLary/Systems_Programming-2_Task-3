  
#include "Road.hpp"
#include "Player.hpp"
#include <iostream>
using std::runtime_error;

Road::Road(int id) : id(id), OwnerPlayer(nullptr) {}

string Road::getPlayerName() const {
    // the condition is know that if the player is nullptr so he go to else
    if (OwnerPlayer) {
        return OwnerPlayer->getName();
    } else {
        return "No player";
    }
}

vector<int> Road::getBetweenVertices() const {
    return betweenVertices;
}

void Road::setBetweenVertices(const vector<int>& vertices) {
    betweenVertices = vertices;
}

vector<int> Road::getAdjacentRoads() const {
    return adjacentRoads;
}

void Road::setAdjacentRoads(const vector<int>& roads) {
    adjacentRoads = roads;
}

bool Road::isOccupied() const {
    return OwnerPlayer != nullptr;
}

void Road::setPlayer(Player* p) {
    if (this->Occupied && this->OwnerPlayer) {
        throw runtime_error("This road is already occupied by another player: " + this->getPlayerName());
    }
    OwnerPlayer = p;
    Occupied = (p != nullptr);
}

int Road::getId() const {
    return id;
}