#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <map>
#include "Tile.hpp" 

class Board;

class Player {
public:
    std::string name;
    int points;
    std::map<ResourceType, int> resources; 
    std::vector<int> settlements; // List of settlement vertex indices


    Player(const std::string &name);
    void placeSettlement(int vertexIndex, Board &board); // שונה לקבל אינדקס של קודקוד
    void placeRoad(int roadIndex, Board &board); // שונה לקבל אינדקס של דרך
    void upgradeSettlementToCity(int vertexIndex, Board &board); // Upgrade a settlement to a city
    void addResource(ResourceType resource, int amount); // הוספת כמות
    void removeResource(ResourceType resource, int amount); // Remove resources from the player
    std::string getName() const;
    int getPoints() const;
};

#endif // PLAYER_HPP
