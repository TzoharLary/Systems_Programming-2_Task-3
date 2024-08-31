#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <map>
#include "DevelopmentCard.hpp"
#include "Road.hpp"
#include <iostream>
#include <iterator>
#include <memory>
#include <algorithm>
#include <random>
/* Explanation of includes in Board.hpp and not in Board.cpp:
*  We include the DevelopmentCard.hpp file in the Board.hpp file 
   because we need to create a field of development cards that we create on the board that the players can buy.
   the mean is that we need it for dreate a deck of development cards that the players can buy.
*  We include the Road.hpp file in the Board.hpp file
   because we need to create a field of roads that we create on the board that the players can build on.
*/
using std::vector;
using std::map;
using std::ostream_iterator;
using std::cout;
using std::endl;
using std::copy;
using std::unique_ptr;
using std::make_unique;
using std::shuffle;
using std::unique_ptr;
using std::unordered_map;

class Player;


class Board {
private:
    vector<Tile> tiles;
    vector<Vertex> vertices;
    vector<Road> roads;
    unordered_map<int, vector<const Road*>> vertexToRoadsMap;
    void addTile(int id, ResourceType resource, int number, const vector<int> indexOfVerticesOfTile, const vector<int>& adjacentTiles);
    void createRoads(); 
    void createVertices();
    void createTiles();
    void createDevelopmentCards();
    void buildVertexToRoadsMap();
    void setup();
    template <typename T>
    void printVector(const vector<T>& vec) const {
        copy(vec.begin(), vec.end(), ostream_iterator<T>(cout, " "));
        cout << "]" << endl;
    }
    // we create a field of development cards that we create on the board that the plaeyrs can buy
    // the unique_ptr is a smart pointer that will delete the object when it goes out of scope
    // and now we can use polymorphism with the development cards.
    vector<unique_ptr<DevelopmentCard>> developmentCards;
    vector<unique_ptr<DevelopmentCard>>& getDeck();


    // void distributeResources(int rolledNumber);
    friend class Player;
    friend class Validator;
    friend class Catan;
public:
    Board();
    vector<Tile*> getTilesForVertex(int vertexIndex);

    /*  Some comment about the functions getAllTiles, getRoads, and getAllVertices:
        This methods for get all the tiles, roads, and vertices
        are return a value and not a reference 
        because we don't want to change the value of the tiles, roads, and vertices
        hence,  we use these methods, it will be in these commands:
        vector<Tile> tiles = board.getAllTiles(); and not vector<Tile>& tiles = board.getAllTiles();
    */
    vector<Tile> getAllTiles() const;
    vector<Road> getRoads() const;
    vector<Vertex> getAllVertices() const;
    // method for get a specific vertex by index
    Vertex getVertex(int index) const;
    Tile getTile(int index) const;
    vector<int> getAdjacentTiles(int tileIndex) const;
    vector<int> getAdjacentVertices(int vertexIndex) const;
    void printAdjacent(int index, bool isTile) const;
    vector<int> getAdjacentVertices(int vertexIndex);
    vector<const Road*> getRoadsOnVertex(int vertexId) const;
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
