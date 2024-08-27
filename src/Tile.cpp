#include "Tile.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Road.hpp"


/* The constructor for the Tile class
    // The const std::vector<Vertex>& vertices indicates that the vector vertices is passed to the function by reference and will not be modified within the function. This saves memory and improves performance by avoiding unnecessary copying.
    // The const std::vector<int>& adjacentTiles indicates that the vector adjacentTiles is passed to the function by reference and will not be modified within the function. This saves memory and improves performance by avoiding unnecessary copying.
*/
Tile::Tile(int id, ResourceType resource, int number, const std::vector<Vertex*>& vertices, const std::vector<int>& adjacentTiles)
    : TileId(id), TileResource(resource), TileNumber(number), TileVertices(vertices), adjacentTiles(adjacentTiles) {}

void Tile::status() const {
    std::cout << "Tile ID: " << TileId << std::endl;
    // ptint the name of the resource of the tile
    std::cout << "Resource: ";
    switch (TileResource) {
        case ResourceType::WOOD:
            std::cout << "WOOD" << std::endl;
            break;
        case ResourceType::BRICK:
            std::cout << "BRICK" << std::endl;
            break;
        case ResourceType::SHEEP:
            std::cout << "SHEEP" << std::endl;
            break;
        case ResourceType::WHEAT:
            std::cout << "WHEAT" << std::endl;
            break;
        case ResourceType::ORE:
            std::cout << "ORE" << std::endl;
            break;
        case ResourceType::DESERT:
            std::cout << "DESERT" << std::endl;
            break;
    }
    std::cout << "Number: " << TileNumber << std::endl;
    std::cout << "Vertices: ";
    for (const Vertex* vertex : TileVertices) {
        std::cout << vertex->getId() << " ";
    }
    std::cout << std::endl;
    std::cout << "Adjacent Tiles: ";
    for (int tile : adjacentTiles) {
        std::cout << tile << " ";
    }
    std::cout << std::endl;
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
        std::vector<const Vertex*> constVertices;
        for (const auto& vertex : TileVertices) {
            constVertices.push_back(vertex);
        }
        return constVertices;
}

// The getNumber function returns the number of the tile.
int Tile::getNumber() const {
    return TileNumber;
}

