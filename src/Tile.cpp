#include "Tile.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Road.hpp"
using std::cout;
using std::endl;



Tile::Tile(int id, ResourceType resource, int number, const vector<Vertex*>& vertices, const vector<int>& adjacentTiles)
    : TileId(id), TileResource(resource), TileNumber(number), TileVertices(vertices), adjacentTiles(adjacentTiles) {}

void Tile::status() const {
    cout << "Tile ID: " << TileId << endl;
    // ptint the name of the resource of the tile
    cout << "Resource: ";
    switch (TileResource) {
        case ResourceType::WOOD:
            cout << "WOOD" << endl;
            break;
        case ResourceType::BRICK:
            cout << "BRICK" << endl;
            break;
        case ResourceType::SHEEP:
            cout << "SHEEP" << endl;
            break;
        case ResourceType::WHEAT:
            cout << "WHEAT" << endl;
            break;
        case ResourceType::ORE:
            cout << "ORE" << endl;
            break;
        case ResourceType::DESERT:
            cout << "DESERT" << endl;
            break;
    }
    cout << "Number: " << TileNumber << endl;
    cout << "Vertices: ";
    for (const Vertex* vertex : TileVertices) {
        cout << vertex->getId() << " ";
    }
    cout << endl;
    cout << "Adjacent Tiles: ";
    for (int tile : adjacentTiles) {
        cout << tile << " ";
    }
    cout << endl;
}


// The getVertex function returns a pointer to the Vertex object at the specified index within the vertices vector of the Tile object.
const Vertex* Tile::getVertex(int id) const {
    for (const auto& vertex : TileVertices) {
        if (vertex->getId() == id) {
            return vertex;
        }
    }
    cout << "I don't find the vertex with the id: " << id << endl;
    return nullptr;
}



int Tile::getId() const {
    return TileId;
}

// The getResource function returns the resource type of the tile.
ResourceType Tile::getResource() const {
    return TileResource;
}

// The getAdjacentTiles function returns a vector of integers representing the adjacent tiles to the tile.
vector<int> Tile::getAdjacentTiles() const {
    return adjacentTiles;
}

// The getVerticesSize function returns the number of vertices on the tile.
int Tile::getVerticesSize() const {
    return TileVertices.size();
}

// method that return vector<Vertex> TileVertices;
vector<const Vertex*> Tile::getVertices() const {
        vector<const Vertex*> constVertices;
        for (const auto& vertex : TileVertices) {
            constVertices.push_back(vertex);
        }
        return constVertices;
}

// The getNumber function returns the number of the tile.
int Tile::getNumber() const {
    return TileNumber;
}

