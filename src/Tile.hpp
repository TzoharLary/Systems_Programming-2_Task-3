#ifndef TILE_HPP
#define TILE_HPP

#include <vector>
#include <map>
#include "Vertex.hpp"
#include "Road.hpp"
using std::vector;

enum ResourceType { WOOD, BRICK, SHEEP, WHEAT, ORE, DESERT };

class Player; // Forward declaration to avoid circular dependency
class Board;  // Forward declaration to avoid circular dependency

class Tile {
public:
    int id; // tile id
    ResourceType resource;
    int number;
    vector<Vertex> vertices; // hold the vertices that are on the tile
    vector<int> adjacentTiles; //  hold the number of the adjacent tiles id to the tile
    Tile(int id, ResourceType resource, int number, const std::vector<Vertex>& vertices, const std::vector<int>& adjacentTiles);
    Vertex* getVertex(int index) const;
    void distributeResources(int rolledNumber, Board& board);
    ResourceType getResource() const;
    int getId() const;
};

#endif // TILE_HPP

// func getVertex: return a pointer to the Vertex object at the specified index within the vertices vector of the Tile object.
// func distributeResources: distribute resources to players based on the rolled number and the vertices of the tile.