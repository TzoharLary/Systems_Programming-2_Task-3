  
#include "Road.hpp"
#include "Player.hpp"
#include <iostream>

Road::Road(int id) : id(id), player(nullptr) {}

std::string Road::getPlayerName() const {
    if (player) {
        return player->getName();
    } else {
        return "No player";
    }
}


int Road::getId() const {
    return id;
}