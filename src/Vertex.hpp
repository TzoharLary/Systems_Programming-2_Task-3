#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>
#include <string>
using std::string;
using std::vector;


class Player;


class Vertex {
public:
    enum VertexType { NONE, SETTLEMENT, CITY };
private:
    int id;                          // The id of the vertex
    bool occupied;                   // If the vertex is occupied
    Player* player;                  // Which player is occupying the vertex
    VertexType type;                 // Type of the vertex
    vector<int> adjacentVertices;    // All the vertices that are adjacent to this vertex
    void setPlayer(Player* p);
    void setType(VertexType newType);
    void setVertexProperties(VertexType newType, Player* p);
    void setAdjacentVertices(const vector<int>& vertices);
    friend class Player;
    friend class Board;

public:
    std::vector<int> getAdjacentVertices() const;
    string getPlayerName() const;
    bool isOccupied() const;
    Player* getPlayer() const;
    Vertex(int idx); 
    VertexType getType() const;
    int getId() const;

};

#endif // VERTEX_HPP
