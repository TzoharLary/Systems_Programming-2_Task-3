  
#include "Road.hpp"
#include "Player.hpp"
#include <iostream>

Road::Road(int id) : id(id), player(nullptr) {}

std::string Road::getPlayerName() const {
    // the condition is know that if the player is nullptr so he go to else
    if (player) {
        return player->getName();
    } else {
        return "No player";
    }
}

std::vector<int> Road::getBetweenVertices() const {
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
    return player != nullptr;
}

void Road::setPlayer(Player* p) {
    if (this->Occupied && this->player) {
        throw std::runtime_error("This road is already occupied by another player: " + this->getPlayerName());
    }
    player = p;
    Occupied = (p != nullptr);
}

int Road::getId() const {
    return id;
}