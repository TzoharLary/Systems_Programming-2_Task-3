#include "Vertex.hpp"
#include "Player.hpp"

Vertex::Vertex(int idx) : id(idx), occupied(false), player(nullptr), type(NONE) {}

std::string Vertex::getPlayerName() const {
    if (player) {
        return player->getName();
    } else {
        return "No player";
    }
}