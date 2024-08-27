#ifndef ROAD_HPP
#define ROAD_HPP
#include <string>
using std::string;
#include <vector>
using std::vector;

class Player;
class Board;

class Road {
private:
    bool Occupied;  // if the road is occupied
    int id;        
    Player* OwnerPlayer;   
    vector<int> betweenVertices; 
    void setPlayer(Player* p);
    void setBetweenVertices(const vector<int>& vertices);
    void setAdjacentRoads(const vector<int>& roads);

    friend class Player;
    friend class Board;
public:
    // move this set to private + add friend class Board
    // because this is the only class that using this set method

    vector<int> adjacentRoads;
    Road(int id);
    // get the vertices near the road
    vector<int> getBetweenVertices() const;
    vector<int> getAdjacentRoads() const;
    string getPlayerName() const;
    int getId() const;    
    bool isOccupied() const;
    

};

#endif // ROAD_HPP
