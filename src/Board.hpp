#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <map>
#include "Tile.hpp"
#include "Vertex.hpp"
#include "Road.hpp"

class Player;

class Board {
private:

    void createRoads(); 
    void createVertices();
    void setup();

public:
    Board();
    std::vector<Tile> tiles;
    std::map<int, Vertex> vertices;
    std::vector<Road> roads;
    Tile getTile(int index) const;
    void addTile(ResourceType resource, int number, const std::vector<Vertex>& vertices, const std::vector<int>& adjacentTiles);
    std::vector<int> getAdjacentTiles(int tileIndex) const;
    std::vector<int> getAdjacentVertices(int vertexIndex) const;
};

#endif // BOARD_HPP
