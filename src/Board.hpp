#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <map>
#include "Tile.hpp"
#include "Vertex.hpp"
#include "Road.hpp"
#include "DevelopmentCard.hpp"
#include <iostream>
#include <iterator>
#include <memory>
#include <algorithm>
#include <random>
using std::vector;
using std::map;
using std::ostream_iterator;
using std::cout;
using std::endl;
using std::copy;
using std::unique_ptr;
using std::make_unique;
using std::shuffle;

class Player;

class Board {
private:
    vector<Tile> tiles;
    vector<Vertex> vertices;
    vector<Road> roads;
    void addTile(int id, ResourceType resource, int number, const std::vector<Vertex>& vertices, const std::vector<int>& adjacentTiles);
    void createRoads(); 
    void createVertices();
    void createTiles();
    void createDevelopmentCards();
    void setup();
    template <typename T>
    void printVector(const vector<T>& vec) const {
        copy(vec.begin(), vec.end(), ostream_iterator<T>(cout, " "));
        cout << "]" << endl;
    }
    // we create a field of development cards that we create on the board that the plaeyrs can buy
    // the unique_ptr is a smart pointer that will delete the object when it goes out of scope
    // and now we can use polymorphism with the development cards.
    vector<std::unique_ptr<DevelopmentCard>> developmentCards;
    friend class Player;
    friend class Validator;

    void distributeResources(int rolledNumber);

public:
    Board();
    vector<Road> getRoads() const;
    vector<Tile*> getTilesForVertex(int vertexIndex);
    Tile getTile(int index) const;
    vector<int> getAdjacentTiles(int tileIndex) const;
    vector<int> getAdjacentVertices(int vertexIndex) const;
    void printAdjacent(int index, bool isTile) const;
    vector<unique_ptr<DevelopmentCard>>& getDeck();

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
