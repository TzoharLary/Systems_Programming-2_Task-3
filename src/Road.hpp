#ifndef ROAD_HPP
#define ROAD_HPP
#include <string>
using std::string;
#include <vector>
using std::vector;

class Player;

class Road {
private:
    bool Occupied;  // if the road is occupied


public:
    int id;        
    Player* player;     
    vector<int> betweenVertices; 
    vector<int> adjacentRoads;
    Road(int id);
    // get the vertices between the road
    vector<int> getBetweenVertices() const;
    void setBetweenVertices(const vector<int>& vertices);
    vector<int> getAdjacentRoads() const;
    void setAdjacentRoads(const vector<int>& roads);
    string getPlayerName() const;
    int getId() const;
    void setPlayer(Player* p);
    bool isOccupied() const;

};

#endif // ROAD_HPP
