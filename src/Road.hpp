#ifndef ROAD_HPP
#define ROAD_HPP
#include <string>
using std::string;

class Player;

class Road {
private:
    bool Occupied;  // if the road is occupied


public:
    int id;         // מזהה הדרך
    Player* player;     // השחקן שבנה את הדרך (0 אם לא תפוס)
    Road(int id);
    string getPlayerName() const;
    int getId() const;
    void setPlayer(Player* p);
    bool isOccupied() const;
    // void setOccupied(bool isOccupied);
};

#endif // ROAD_HPP
