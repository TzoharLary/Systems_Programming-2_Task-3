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
    int id;                          // מזהה הקודקוד
    bool occupied;                   // האם הקודקוד תפוס
    Player* player;                      // מזהה השחקן שתפס את הקודקוד
    VertexType type;                 // סוג התפוסה (יישוב או עיר)
    vector<int> adjacentVertices; // קודקודים סמוכים
    string getPlayerName() const;
    Vertex(int idx); 
    void setType(VertexType newType);
    VertexType getType() const;
    int getId() const;

};

#endif // VERTEX_HPP
