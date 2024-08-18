#include "Tile.hpp"
#include "Player.hpp"
#include "Board.hpp"


/* The constructor for the Tile class
    // The const std::vector<Vertex>& vertices indicates that the vector vertices is passed to the function by reference and will not be modified within the function. This saves memory and improves performance by avoiding unnecessary copying.
    // The const std::vector<int>& adjacentTiles indicates that the vector adjacentTiles is passed to the function by reference and will not be modified within the function. This saves memory and improves performance by avoiding unnecessary copying.
*/
Tile::Tile(int id, ResourceType resource, int number, const std::vector<Vertex>& vertices, const std::vector<int>& adjacentTiles)
    : id(id), resource(resource), number(number), vertices(vertices), adjacentTiles(adjacentTiles) {}

// The getVertex function returns a pointer to the Vertex object at the specified index within the vertices vector of the Tile object.
Vertex* Tile::getVertex(int index) const {
    if (index < 0 || index >= static_cast<int>(vertices.size())) {
        throw std::out_of_range("Invalid vertex index");
    }
    return const_cast<Vertex*>(&vertices.at(index));
}

int Tile::getId() const {
    return id;
}

// The getResource function returns the resource type of the tile.
ResourceType Tile::getResource() const {
    return resource;
}

void Tile::distributeResources(int rolledNumber, Board& board) {
    // auto& tile: Indicates that the variable tile is a reference to the original variable within the vector board.tiles, preventing unnecessary copying of the tile.
    // const auto& vertex: Indicates that the variable vertex is a const reference to the original Vertex object within the vector tile.vertices, preventing unintended modification and unnecessary copying.
    for (auto& tile : board.tiles) {
        if (tile.number != rolledNumber) {
            continue;
        }
        for (const auto& vertex : tile.vertices) {
            if (vertex.isOccupied()) {
                Player* player = vertex.getPlayer();
                if (vertex.getType() == Vertex::VertexType::SETTLEMENT) {
                    player->addResource(tile.resource, 1);
                } else if (vertex.getType() == Vertex::VertexType::CITY) {
                    player->addResource(tile.resource, 2);
                }
            }
        }
    }
}