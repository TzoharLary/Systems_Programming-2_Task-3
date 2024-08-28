#ifndef TILE_HPP
#define TILE_HPP

#include <vector>
#include <map>
#include "Vertex.hpp"
using std::vector;

/* Explanation of includes in Tile.hpp:
*  We include the Vertex.hpp file in the Tile.hpp file
   because we need to create a field of vertices that we create on the tile that the players can build on.
*/

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
    int TileId; 
    ResourceType TileResource;
    int TileNumber;
    vector<Vertex*> TileVertices;
    vector<int> adjacentTiles; 



public:
    // Constructor for the Tile class
    Tile(int id, ResourceType resource, int number, const vector<Vertex*>& vertices, const vector<int>& adjacentTiles);
    /* Methods Explanation:
    *  getVertex: return a pointer to the Vertex object at the specified index within the vertices vector of the Tile object.
    *  getResource: return the resource type of the tile.
    *  getAdjacentTiles: return a vector of integers representing the adjacent tiles to the tile.
    *  getVerticesSize: return the number of vertices on the tile.
    *  getVertices: return vector<Vertex> TileVertices.
    *  getNumber: return the number of the tile.
    *  getId: return the id of the tile.
    */
    const Vertex* getVertex(int id) const;
    vector<const Vertex*> getVertices() const;
    ResourceType getResource() const;
    int getId() const;
    vector<int> getAdjacentTiles() const;
    int getVerticesSize() const;
    int getNumber() const;
    void status() const;
};

#endif // TILE_HPP

// func getVertex: return a pointer to the Vertex object at the specified index within the vertices vector of the Tile object.
