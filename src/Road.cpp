  
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
/*
// function to set the occupied status of the road
void Road::setOccupied(bool isOccupied) {
    if (this->Occupied && this->player) {
        throw std::runtime_error("This road is already occupied by another player: " + this->getPlayerName());
    }
    this->Occupied = isOccupied;
}
*/

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