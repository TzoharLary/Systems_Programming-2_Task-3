#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>

class Player;

enum VertexType { NONE, SETTLEMENT, CITY };

class Vertex {
public:
    int id;                          // מזהה הקודקוד
    bool occupied;                   // האם הקודקוד תפוס
    Player* player;                      // מזהה השחקן שתפס את הקודקוד
    VertexType type;                 // סוג התפוסה (יישוב או עיר)
    std::vector<int> adjacentVertices; // קודקודים סמוכים

Vertex(int idx); 
};

#endif // VERTEX_HPP
