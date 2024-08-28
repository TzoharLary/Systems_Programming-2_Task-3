#include "Vertex.hpp"
#include "Player.hpp"
using std::runtime_error;

using VertexType = Vertex::VertexType;


/* Explain the concstructor of Vertex:
    * The Vertex constructor initializes like this:  
    * He gets an integer index as a parameter and initializes the id field with it.
    * The occupied field is initialized to false.
    * The player field is initialized to nullptr.
    * The type field is initialized to NONE.
*/
Vertex::Vertex(int idx) :  id(idx), occupied(false), player(nullptr), type(NONE) {}

void Vertex::status() const {
    cout << "This is the status of the vertex: " << id << endl;
    if (occupied) {
        cout << "The vertex is occupied" << endl;
    } else {
        cout << "The vertex is not occupied" << endl;
    }
    if(type == SETTLEMENT){
        cout << "The vertex is a settlement" << endl;
    }
    if (type == CITY){
        cout << "The vertex is a city" << endl;
    }
    if (type == NONE){
        cout << "The vertex is NONE" << endl;
    }
    if (player == nullptr){
        cout << "The vertex is not belong by any player" << endl;
    }
    else{
        cout << "The vertex is occupied by player: " << player->getName() << endl;
    }

    cout << "Adjacent vertices: ";
    for (int vertex : adjacentVertices) {
        cout << vertex << " ";
    }
    cout << endl;
}

void Vertex::setAdjacentVertices(const vector<int>& vertices) {
    adjacentVertices = vertices;
}

bool Vertex::isOccupied() const {
    if (occupied) {
        return true;
    } else {
        return false;
    }
}

void Vertex::setType(VertexType newType) {
    this->type = newType;
}

void Vertex::setPlayer(Player* p) {
    if (this->occupied && this->player) {
        throw runtime_error("This vertex is already occupied by another player: " + this->getPlayerName());
    }
    player = p;
    occupied = true;
}

void Vertex::setVertexProperties(VertexType newType, Player* p) {
    // Set the type of the vertex
    setType(newType);
    // Set the player occupying the vertex
    if(newType == SETTLEMENT){
        setPlayer(p);
    }
}

Player* Vertex::getPlayer() const {
    return player;
}

vector<int> Vertex::getAdjacentVertices() const {
    return adjacentVertices;
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