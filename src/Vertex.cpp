#include "Vertex.hpp"
#include "Player.hpp"
using VertexType = Vertex::VertexType;

Vertex::Vertex(int idx) : id(idx), occupied(false), player(nullptr), type(NONE) {}

void Vertex::setType(VertexType newType) {
    this->type = newType;
}

int Vertex::getId() const {
    return id;
}

VertexType Vertex::getType() const {
    return type;
}

string Vertex::getPlayerName() const {
    if (player) {
        return player->getName();
    } else {
        return "No player";
    }
}