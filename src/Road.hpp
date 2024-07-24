#ifndef ROAD_HPP
#define ROAD_HPP
#include <string>
using std::string;

class Player;

class Road {
private:
    bool Occupied;  // if the road is occupied


public:
    int id;        
    Player* player;     
    vector<int> betweenVertices; 
    Road(int id);
    // get the vertices between the road
    vector<int> getBetweenVertices() const;
    void setBetweenVertices(const vector<int>& vertices);
    string getPlayerName() const;
    int getId() const;
    void setPlayer(Player* p);
    bool isOccupied() const;
    // void setOccupied(bool isOccupied);
};

#endif // ROAD_HPP
