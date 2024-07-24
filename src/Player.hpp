#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <map>
#include "Tile.hpp" 
#include <stdexcept>
#include <iostream>
#include <algorithm>
using std::string;
using std::map;
using std::vector;
using std::runtime_error;
using std::cout;
using std::endl;
using std::find;
using std::out_of_range;

class Validator;
class Board;

class Player {

public:
    string name;
    int points;
    map<ResourceType, int> resources; 
    vector<int> settlements; // List of settlement vertex indices
    vector<int> Citys; // List of Citys vertex indices
    Player(const string &name); 
    void placeSettlement(int vertexIndex, Board &board); // שונה לקבל אינדקס של קודקוד
    void placeRoad(int roadIndex, Board &board); // שונה לקבל אינדקס של דרך
    void upgradeSettlementToCity(int vertexIndex, Board &board); // Upgrade a settlement to a city
    void addResource(ResourceType resource, int amount); // הוספת כמות
    void removeResource(ResourceType resource, int amount); // Remove resources from the player
    string getName() const;
    int getPoints() const;


private:
    enum BuyType { ROAD, SETTLEMENT, CITY, DEVELOPMENT_CARD };
    // Helper function to check and print missing resources
    bool checkResources(const map<ResourceType, int>& cost);
    string resourceTypeToString(ResourceType type);
    void Buy(BuyType type);

};

#endif // PLAYER_HPP
