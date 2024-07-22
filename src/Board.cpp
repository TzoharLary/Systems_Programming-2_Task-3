#include "Board.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Player.hpp"

Board::Board() {
    setup();
}

void Board::setup() {
    createRoads();
    createVertices();
    addTile(ORE, 10, {0, 1, 2, 8, 9, 10}, {1, 3, 4});
    addTile(SHEEP, 2, {2, 3, 4, 12, 11, 10}, {0, 2, 4, 5});
    addTile(WOOD, 9, {4, 5, 6, 12, 13, 14}, {1, 5, 6});
    addTile(WHEAT, 12, {7, 8, 9, 17, 18, 19}, {0, 4, 7, 8});
    addTile(BRICK, 6, {9, 10, 11, 19, 20, 21}, {0, 1, 5, 9, 8, 3});
    addTile(SHEEP, 4, {11, 12, 13, 21, 22, 23}, {1, 2, 4, 6, 9, 10});
    addTile(BRICK, 10, {13, 14, 15, 23, 24, 25}, {2, 5, 10, 11});
    addTile(WHEAT, 9, {16, 17, 18, 27, 28, 29}, {3, 8, 12});
    addTile(WOOD, 11, {18, 19, 20, 29, 30, 31}, {3, 4, 7, 9, 12, 13});
    addTile(DESERT, 0, {20, 21, 22, 31, 32, 33}, {4, 5, 8, 10, 13, 14});
    addTile(WOOD, 3, {22, 23, 24, 33, 34, 35}, {5, 6, 9, 11, 14, 15});
    addTile(ORE, 8, {24, 25, 26, 35, 36, 37}, {6, 10, 15});
    addTile(WOOD, 8, {28, 29, 30, 38, 39, 40}, {7, 8, 13, 16});
    addTile(ORE, 3, {30, 31, 32, 40, 41, 42}, {8, 9, 12, 14, 16, 17});
    addTile(WHEAT, 4, {32, 33, 34, 42, 43, 44}, {9, 10, 13, 15, 17, 18});
    addTile(SHEEP, 5, {34, 35, 36, 44, 45, 46}, {10, 11, 14, 18});
    addTile(BRICK, 5, {39, 40, 41, 47, 48, 49}, {12, 13, 17});
    addTile(WHEAT, 6, {41, 42, 43, 49, 50, 51}, {13, 14, 16, 18});
    addTile(SHEEP, 11, {43, 44, 45, 51, 52, 53}, {14, 15, 17});
}

void Board::createRoads() {
    for (int i = 0; i < 72; ++i) {
         // We used emplace() instead of insert() because 
        // we want to construct the Road object in place
        // and avoid copying it from a temporary object
        roads.emplace_back(i); 
    }
}

void Board::createVertices() {
    for (int i = 0; i < 54; ++i) { // assume 54 vertices
        // We used emplace() instead of insert() because
        // we want to construct the Vertex object in place
        // and avoid copying it from a temporary object
        // the next line creates a new Vertex object with the given id
        vertices.emplace(i, Vertex(i)); 
    }
}

void Board::addTile(ResourceType resource, int number, const std::vector<Vertex>& vertices, const std::vector<int>& adjacentTiles) {
    // Create a new Tile object with the given resource, number, vertices, and adjacentTiles
    Tile newTile(resource, number, vertices, adjacentTiles);

    // Adding the vertices of the tile from the pre-created map.
    for (const auto& vertex : vertices) {
        // Check if the vertexId exists in the pre-created vertices map
        if (this->vertices.find(vertex.id) == this->vertices.end()) {
            // If the vertexId does not exist, throw an error
            throw std::runtime_error("Vertex ID does not exist in the vertices map");
        }
        // Add the vertex to the new tile's settlements map
        // we used
        newTile.vertices.push_back(vertex);
    }

    // Add the new tile to the board's tiles vector
    tiles.push_back(newTile);
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
    if (vertices.find(vertexIndex) == vertices.end()) {
        throw std::out_of_range("Invalid vertex index");
    }
    return vertices.at(vertexIndex).adjacentVertices; // שימוש בפונקציה at() במקום אופרטור []
}