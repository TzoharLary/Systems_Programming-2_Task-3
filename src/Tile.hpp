#ifndef TILE_HPP
#define TILE_HPP

#include <vector>
#include <map>
#include "Vertex.hpp"
#include "Road.hpp"

enum ResourceType { WOOD, BRICK, SHEEP, WHEAT, ORE, DESERT };

class Player; // Forward declaration to avoid circular dependency
class Board;  // Forward declaration to avoid circular dependency

class Tile {
public:
    ResourceType resource;
    int number;
    // std::map<int, Vertex> settlements; // hold the settlements that are on the tile
    std::vector<Vertex> vertices; // hold the vertices that are on the tile
    std::vector<int> adjacentTiles; //  hold the adjacent tiles to the tile
    Tile(ResourceType resource, int number, const std::vector<Vertex>& vertices, const std::vector<int>& adjacentTiles);

    void distributeResources(int rolledNumber, Board& board);
};

#endif // TILE_HPP
