#include "Tile.hpp"
#include "Player.hpp"
#include "Board.hpp"


// The constructor for the Tile class
Tile::Tile(ResourceType resource, int number, const std::vector<Vertex>& vertices, const std::vector<int>& adjacentTiles)
    : resource(resource), number(number), vertices(vertices), adjacentTiles(adjacentTiles) {}
    // The const std::vector<Vertex>& vertices indicates that the vector vertices is passed to the function by reference and will not be modified within the function. This saves memory and improves performance by avoiding unnecessary copying.
    // The const std::vector<int>& adjacentTiles indicates that the vector adjacentTiles is passed to the function by reference and will not be modified within the function. This saves memory and improves performance by avoiding unnecessary copying.

void Tile::distributeResources(int rolledNumber, Board& board) {
    // auto& tile: Indicates that the variable tile is a reference to the original variable within the vector board.tiles, preventing unnecessary copying of the tile.
    // const auto& vertex: Indicates that the variable vertex is a const reference to the original Vertex object within the vector tile.vertices, preventing unintended modification and unnecessary copying.
    for (auto& tile : board.tiles) {
        if (tile.number != rolledNumber) {
            continue;
        }
        //asd
        for (const auto& vertex : tile.vertices) {
            if (vertex.player != nullptr) {
                Player* player = vertex.player;
                if (vertex.type == SETTLEMENT) {
                    player->addResource(tile.resource, 1);
                } else if (vertex.type == CITY) {
                    player->addResource(tile.resource, 2);
                }
            }
        }
    }
}