#include "Board.hpp"
#include <stdexcept>
#include <vector>
#include "Player.hpp"

Board::Board() {
    setup();
}

void Board::setup() {
    createRoads();
    createVertices();
    createTiles();
}

void Board::createRoads() {
    for (int i = 0; i < 72; ++i) {
         // We used emplace() instead of insert() because 
        // we want to construct the Road object in place
        // and avoid copying it from a temporary object
        roads.emplace_back(i); 
    }
    // create the vertices that the road is connected to
    roads[0].setBetweenVertices({0, 1});
    roads[1].setBetweenVertices({1, 2});
    roads[2].setBetweenVertices({2, 3});    
    roads[3].setBetweenVertices({3, 4});
    roads[4].setBetweenVertices({4, 5});
    roads[5].setBetweenVertices({5, 6});
    roads[6].setBetweenVertices({7, 8});
    roads[7].setBetweenVertices({8, 9});
    roads[8].setBetweenVertices({9, 10});
    roads[9].setBetweenVertices({10, 11});
    roads[10].setBetweenVertices({11, 12});
    roads[11].setBetweenVertices({12, 13});
    roads[12].setBetweenVertices({13, 14});
    roads[13].setBetweenVertices({14, 15});
    roads[14].setBetweenVertices({16, 17});
    roads[15].setBetweenVertices({17, 18});
    roads[16].setBetweenVertices({18, 19});
    roads[17].setBetweenVertices({19, 20});
    roads[18].setBetweenVertices({20, 21});
    roads[19].setBetweenVertices({21, 22});
    roads[20].setBetweenVertices({22, 23});
    roads[21].setBetweenVertices({23, 24});
    roads[22].setBetweenVertices({24, 25});
    roads[23].setBetweenVertices({25, 26});
    roads[24].setBetweenVertices({27, 28});
    roads[25].setBetweenVertices({28, 29});
    roads[26].setBetweenVertices({29, 30});
    roads[27].setBetweenVertices({30, 31});
    roads[28].setBetweenVertices({31, 32});
    roads[29].setBetweenVertices({32, 33});
    roads[30].setBetweenVertices({33, 34});
    roads[31].setBetweenVertices({34, 35});
    roads[32].setBetweenVertices({35, 36});
    roads[33].setBetweenVertices({36, 37});
    roads[34].setBetweenVertices({38, 39});
    roads[35].setBetweenVertices({39, 40});
    roads[36].setBetweenVertices({40, 41});
    roads[37].setBetweenVertices({41, 42});
    roads[38].setBetweenVertices({42, 43});
    roads[39].setBetweenVertices({43, 44});
    roads[40].setBetweenVertices({44, 45});
    roads[41].setBetweenVertices({45, 46});
    roads[42].setBetweenVertices({47, 48});
    roads[43].setBetweenVertices({48, 49});
    roads[44].setBetweenVertices({49, 50});
    roads[45].setBetweenVertices({50, 51});
    roads[46].setBetweenVertices({51, 52});
    roads[47].setBetweenVertices({52, 53});
    roads[48].setBetweenVertices({0, 8});
    roads[49].setBetweenVertices({7, 17});
    roads[50].setBetweenVertices({16, 27});
    roads[51].setBetweenVertices({28, 38});
    roads[52].setBetweenVertices({39, 47});
    roads[53].setBetweenVertices({2, 10});
    roads[54].setBetweenVertices({9, 19});
    roads[55].setBetweenVertices({18, 29});
    roads[56].setBetweenVertices({20, 31});
    roads[57].setBetweenVertices({30, 40});
    roads[58].setBetweenVertices({41, 49});
    roads[59].setBetweenVertices({4, 12});
    roads[60].setBetweenVertices({11, 21});
    roads[61].setBetweenVertices({22, 33});
    roads[62].setBetweenVertices({32, 42});
    roads[63].setBetweenVertices({43, 51});
    roads[64].setBetweenVertices({6, 14});
    roads[65].setBetweenVertices({13, 23});
    roads[66].setBetweenVertices({24, 35});
    roads[67].setBetweenVertices({34, 44});
    roads[68].setBetweenVertices({45, 53});
    roads[69].setBetweenVertices({15, 25});
    roads[70].setBetweenVertices({26, 37});
    roads[71].setBetweenVertices({36, 46});
}

void Board::createVertices() {
    for (int i = 0; i < 54; i++) { 
        // assume 54 vertices
        // We used emplace() instead of insert() because
        // we want to construct the Vertex object in place
        // and avoid copying it from a temporary object
        // the next line creates a new Vertex object with the given id
        vertices.emplace_back(i); 
    }
    // create the adjacent vertices for each vertex
    vertices[0].setAdjacentVertices({1, 8});
    vertices[1].setAdjacentVertices({0, 2});
    vertices[2].setAdjacentVertices({1, 3, 10});
    vertices[3].setAdjacentVertices({2, 4});
    vertices[4].setAdjacentVertices({3, 5, 12});
    vertices[5].setAdjacentVertices({4, 6});
    vertices[6].setAdjacentVertices({5, 14});
    vertices[7].setAdjacentVertices({8, 17});
    vertices[8].setAdjacentVertices({0, 7, 9});
    vertices[9].setAdjacentVertices({8, 10, 19});
    vertices[10].setAdjacentVertices({2,9,11});
    vertices[11].setAdjacentVertices({10,12,21});
    vertices[12].setAdjacentVertices({4,11,13});
    vertices[13].setAdjacentVertices({12,14,23});
    vertices[14].setAdjacentVertices({6,13,15});
    vertices[15].setAdjacentVertices({14,25});
    vertices[16].setAdjacentVertices({17, 27});
    vertices[17].setAdjacentVertices({7,16,18});
    vertices[18].setAdjacentVertices({17, 19, 29});
    vertices[19].setAdjacentVertices({9, 18, 20});
    vertices[20].setAdjacentVertices({19, 21, 31});
    vertices[21].setAdjacentVertices({11, 20, 22});
    vertices[22].setAdjacentVertices({21, 23, 33});
    vertices[23].setAdjacentVertices({13, 22, 24});
    vertices[24].setAdjacentVertices({23, 25, 35});
    vertices[25].setAdjacentVertices({15, 24, 26});
    vertices[26].setAdjacentVertices({25, 37});
    vertices[27].setAdjacentVertices({16, 28});
    vertices[28].setAdjacentVertices({27, 29, 38});
    vertices[29].setAdjacentVertices({18, 28, 30});
    vertices[30].setAdjacentVertices({29, 31, 40});
    vertices[31].setAdjacentVertices({20, 30, 32});
    vertices[32].setAdjacentVertices({31, 33, 42});
    vertices[33].setAdjacentVertices({22, 32, 34});
    vertices[34].setAdjacentVertices({33, 35, 44});
    vertices[35].setAdjacentVertices({24, 34, 36});
    vertices[36].setAdjacentVertices({35, 37, 46});
    vertices[37].setAdjacentVertices({26, 36});
    vertices[38].setAdjacentVertices({28, 39});
    vertices[39].setAdjacentVertices({38, 40, 47});
    vertices[40].setAdjacentVertices({30, 39, 41});
    vertices[41].setAdjacentVertices({40, 42, 49});
    vertices[42].setAdjacentVertices({32, 41, 43});
    vertices[43].setAdjacentVertices({42, 44, 51});
    vertices[44].setAdjacentVertices({34, 43, 45});
    vertices[45].setAdjacentVertices({44, 46, 53});
    vertices[46].setAdjacentVertices({36, 46});
    vertices[47].setAdjacentVertices({39, 48});
    vertices[48].setAdjacentVertices({47, 49});
    vertices[49].setAdjacentVertices({48, 41, 50});
    vertices[50].setAdjacentVertices({49, 51});
    vertices[51].setAdjacentVertices({43, 50, 52});
    vertices[52].setAdjacentVertices({51, 53});
    vertices[53].setAdjacentVertices({45, 52});
    // this.printAdjacent(0, false);


}

void Board::createTiles() {
    // Create the tiles of the board
    addTile(0, ORE, 10, {0, 1, 2, 8, 9, 10}, {1, 3, 4});
    addTile(1, SHEEP, 2, {2, 3, 4, 12, 11, 10}, {0, 2, 4, 5});
    addTile(2, WOOD, 9, {4, 5, 6, 12, 13, 14}, {1, 5, 6});
    addTile(3, WHEAT, 12, {7, 8, 9, 17, 18, 19}, {0, 4, 7, 8});
    addTile(4, BRICK, 6, {9, 10, 11, 19, 20, 21}, {0, 1, 5, 9, 8, 3});
    addTile(5, SHEEP, 4, {11, 12, 13, 21, 22, 23}, {1, 2, 4, 6, 9, 10});
    addTile(6, BRICK, 10, {13, 14, 15, 23, 24, 25}, {2, 5, 10, 11});
    addTile(7, WHEAT, 9, {16, 17, 18, 27, 28, 29}, {3, 8, 12});
    addTile(8, WOOD, 11, {18, 19, 20, 29, 30, 31}, {3, 4, 7, 9, 12, 13});
    addTile(9, DESERT, 0, {20, 21, 22, 31, 32, 33}, {4, 5, 8, 10, 13, 14});
    addTile(10, WOOD, 3, {22, 23, 24, 33, 34, 35}, {5, 6, 9, 11, 14, 15});
    addTile(11, ORE, 8, {24, 25, 26, 35, 36, 37}, {6, 10, 15});
    addTile(12, WOOD, 8, {28, 29, 30, 38, 39, 40}, {7, 8, 13, 16});
    addTile(13, ORE, 3, {30, 31, 32, 40, 41, 42}, {8, 9, 12, 14, 16, 17});
    addTile(14, WHEAT, 4, {32, 33, 34, 42, 43, 44}, {9, 10, 13, 15, 17, 18});
    addTile(15, SHEEP, 5, {34, 35, 36, 44, 45, 46}, {10, 11, 14, 18});
    addTile(16, BRICK, 5, {39, 40, 41, 47, 48, 49}, {12, 13, 17});
    addTile(17, WHEAT, 6, {41, 42, 43, 49, 50, 51}, {13, 14, 16, 18});
    addTile(18, SHEEP, 11, {43, 44, 45, 51, 52, 53}, {14, 15, 17});
}

void Board::addTile(int id, ResourceType resource, int number, const vector<Vertex>& verticesOfTile, const vector<int>& adjacentTiles) {
    
    for (const auto& vertex : verticesOfTile) {
        /*  If the vertex is not in the vector of vertices of the tile,
            an error is thrown because the vertex should exist
            in the vector before adding it to the new slot.
            the condition says that for each vertex in the vertices vector
            if the vertex id is not in the vertices vector throw an error
        */
        if (vertex.getId() < 0 || vertex.getId() >= static_cast<int>(vertices.size())) {
            // If the vertexId does not exist, throw an error
            throw std::runtime_error("Vertex ID does not exist in the vertices vector that the tile is being added to");
        }
    }
    // Create a new Tile object with the given resource, number, vertices, and adjacentTiles
    Tile newTile(id, resource, number, verticesOfTile, adjacentTiles);

    // Add the new tile to the board's tiles vector
    tiles.push_back(newTile);
}

vector<Tile*> Board::getTilesForVertex(int vertexIndex) {

    vector<Tile*> tilesForVertex;
    // Iterate over all the tiles in the board
    for (Tile& tile : tiles) {
        // Iterate over all the vertices of the tile and check if the vertexIndex matches
        // the cast to int is necessary because the size() method returns an unsigned integer
        for (int i = 0; i < static_cast<int>(tile.vertices.size()); ++i) {
            // create a pointer to the current vertex in the tile
            Vertex* vertex = tile.getVertex(i);
            // Check if the vertex is not null and the index matches the vertexIndex
            if (vertex->getId() == vertexIndex) {
                tilesForVertex.push_back(&tile);
                break;
            }
        }
    }
    return tilesForVertex;
}

Tile Board::getTile(int index) const {
    if (index < 0 || index >= static_cast<int>(tiles.size())) {
        throw std::out_of_range("Invalid tile index");
    }
    return tiles[index];
}

std::vector<int> Board::getAdjacentTiles(int tileIndex) const {
    if (tileIndex < 0 || tileIndex >= static_cast<int>(tiles.size())) {
        throw std::out_of_range("Invalid tile index");
    }
    return tiles[tileIndex].adjacentTiles;
}

std::vector<int> Board::getAdjacentVertices(int vertexIndex) const {
    if (vertexIndex < 0 || vertexIndex >= static_cast<int>(vertices.size())) {
        // If the vertexId does not exist, throw an error
        throw std::runtime_error("Vertex ID does not exist in the vertices vector that the tile is being added to");
    }
    return vertices.at(vertexIndex).adjacentVertices; 
}


// Functions for test purposes:
void Board::printAdjacent(int index, bool isTile) const {
    std::vector<int> result;
    if (isTile) {
        result = getAdjacentTiles(index);
    } else {
        result = getAdjacentVertices(index);
    }
    cout << (isTile ? "this is the Adjacent of the Tiles: " : "this is the Adjacent of the Vertices: ") << "[ "; 
    printVector(result);
    cout << "\n";
}