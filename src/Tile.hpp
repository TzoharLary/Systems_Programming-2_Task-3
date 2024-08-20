#ifndef TILE_HPP
#define TILE_HPP

#include <vector>
#include <map>
#include "Vertex.hpp"
#include "Road.hpp"
using std::vector;

enum ResourceType { WOOD, BRICK, SHEEP, WHEAT, ORE, DESERT };

class Player; 
class Board;  

class Tile {

private:
    /* Fields Explanation:
    *  TileId: The id of the tile
    *  TileResource: The resource type of the tile
    *  TileNumber: The number of the tile
    *  TileVertices: The vertices that are on the tile
    *  adjacentTiles: The adjacent tiles to the tile
    */
    int TileId; // tile id
    ResourceType TileResource;
    int TileNumber;
    vector<Vertex> TileVertices; // hold the vertices that are on the tile
    vector<int> adjacentTiles; //  hold the number of the adjacent tiles id to the tile



public:
    // Constructor for the Tile class
    Tile(int id, ResourceType resource, int number, const std::vector<Vertex>& vertices, const std::vector<int>& adjacentTiles);
    /* Methods Explanation:
    *  getVertex: return a pointer to the Vertex object at the specified index within the vertices vector of the Tile object.
    *  getResource: return the resource type of the tile.
    *  getAdjacentTiles: return a vector of integers representing the adjacent tiles to the tile.
    *  getVerticesSize: return the number of vertices on the tile.
    *  getVertices: return vector<Vertex> TileVertices.
    *  getNumber: return the number of the tile.
    *  getId: return the id of the tile.
    */
    const Vertex* getVertex(int index) const;
    const vector<Vertex>& getVertices() const;
    ResourceType getResource() const;
    int getId() const;
    vector<int> getAdjacentTiles() const;
    int getVerticesSize() const;
    int getNumber() const;
};

#endif // TILE_HPP

// func getVertex: return a pointer to the Vertex object at the specified index within the vertices vector of the Tile object.
