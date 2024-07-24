#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <map>
#include "Tile.hpp"
#include "Vertex.hpp"
#include "Road.hpp"
using std::vector;
using std::map;

class Player;

class Board {
private:

    void createRoads(); 
    void createVertices();
    void setup();

public:
    Board();
    vector<Tile> tiles;
    map<int, Vertex> vertices;
    vector<Road> roads;
    vector<Tile*> getTilesForVertex(int vertexIndex);
    Tile getTile(int index) const;
    void addTile(ResourceType resource, int number, const std::vector<Vertex>& vertices, const std::vector<int>& adjacentTiles);
    vector<int> getAdjacentTiles(int tileIndex) const;
    vector<int> getAdjacentVertices(int vertexIndex) const;
};

#endif // BOARD_HPP


// func createRoads: create the roads of the board.
// func createVertices: create the vertices of the board.
// func setup: create the tiles, roads, and vertices of the board.
// func getTilesForVertex: return a vector of pointers to the tiles that contain the specified vertex.
// func getTile: return the tile at the specified index.
// func addTile: add a new tile to the board with the specified resource, number, vertices, and adjacent tiles.
// func getAdjacentTiles: return the indices of the adjacent tiles to the specified tile.
// func getAdjacentVertices: return the indices of the adjacent vertices to the specified vertex.
