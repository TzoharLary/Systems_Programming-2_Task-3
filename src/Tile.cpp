#include "Tile.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Road.hpp"


/* The constructor for the Tile class
    // The const std::vector<Vertex>& vertices indicates that the vector vertices is passed to the function by reference and will not be modified within the function. This saves memory and improves performance by avoiding unnecessary copying.
    // The const std::vector<int>& adjacentTiles indicates that the vector adjacentTiles is passed to the function by reference and will not be modified within the function. This saves memory and improves performance by avoiding unnecessary copying.
*/
Tile::Tile(int id, ResourceType resource, int number, const std::vector<Vertex>& vertices, const std::vector<int>& adjacentTiles)
    : TileId(id), TileResource(resource), TileNumber(number), TileVertices(vertices), adjacentTiles(adjacentTiles) {}

// The getVertex function returns a pointer to the Vertex object at the specified index within the vertices vector of the Tile object.
const Vertex* Tile::getVertex(int index) const {
    if (index < 0 || index >= static_cast<int>(TileVertices.size())) {
        throw std::out_of_range("Invalid vertex index");
    }
    return &TileVertices.at(index);
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
const vector<Vertex>& Tile::getVertices() const {
    return TileVertices;
}

// The getNumber function returns the number of the tile.
int Tile::getNumber() const {
    return TileNumber;
}

// void Tile::distributeResources(int rolledNumber, Board& board) {
//     // auto& tile: Indicates that the variable tile is a reference to the original variable within the vector board.tiles, preventing unnecessary copying of the tile.
//     // const auto& vertex: Indicates that the variable vertex is a const reference to the original Vertex object within the vector tile.vertices, preventing unintended modification and unnecessary copying.
//     for (auto& tile : board.tiles) {
//         if (tile.TileNumber != rolledNumber) {
//             continue;
//         }
//         for (const auto& vertex : tile.TileVertices) {
//             if (vertex.isOccupied()) {
//                 Player* player = vertex.getPlayer();
//                 if (vertex.getType() == Vertex::VertexType::SETTLEMENT) {
//                     player->addResource(tile.TileResource, 1);
//                 } else if (vertex.getType() == Vertex::VertexType::CITY) {
//                     player->addResource(tile.TileResource, 2);
//                 }
//             }
//         }
//     }
// }