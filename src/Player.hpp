#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <map>
#include "Tile.hpp" 
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <sstream>
using std::string;
using std::map;
using std::vector;
using std::runtime_error;
using std::cout;
using std::endl;
using std::find;
using std::out_of_range;
using std::unique_ptr;

class Validator;
class Board;
class DevelopmentCard;

class Player {

private:
    enum BuyType { ROAD, SETTLEMENT, CITY, DEVELOPMENT_CARD };
    // Helper function to check and print missing resources
    bool checkResources(const map<ResourceType, int>& cost);
    string resourceTypeToString(ResourceType type) const;
    void Buy(BuyType type);
    ResourceType stringToResourceType(const std::string& str) const; // פונקציה חדשה

    // we create a field that hold the development cards of the player
    vector<unique_ptr<DevelopmentCard>> developmentCards;
    int knightCount;
    int victoryPoints;
    Board& board;

public:
    string name;
    int points;
    map<ResourceType, int> resources; 
    vector<int> settlements; // List of settlement vertex indices
    int Citys; // List of Citys vertex indices
    Player(const string& name, Board& board); // נוסיף הפניה ללוח
    void placeSettlement(int vertexIndex); // שונה כך שלא יקבל Board כפרמטר
    void placeRoad(int roadIndex); // שונה כך שלא יקבל Board כפרמטר
    void upgradeSettlementToCity(int vertexIndex); // שונה כך שלא יקבל Board כפרמטר
    void addResource(ResourceType resource, int amount); // הוספת כמות
    void removeResource(ResourceType resource, int amount); // Remove resources from the player
    
    void incrementNumOfCity();
    void incrementPoints();
    void incrementKnightCount();
    void incrementVictoryPoints();

    void Trade(Player& player, ResourceType give, int giveAmount, ResourceType take, int takeAmount);  
    void setResources(const map<ResourceType, int>& newResources);
   
    map<ResourceType, int> getResources() const;
    int getKnightCount() const;
    string getName() const;
    int getPoints() const;
    int getNumOfCity() const;
    void status() const;
    int getNumOfRoads() const;
    const std::vector<std::unique_ptr<DevelopmentCard>>& getDevelopmentCards() const;


    void buyDevelopmentCard();
    void addDevelopmentCard(std::unique_ptr<DevelopmentCard> card);
    void useDevelopmentCard(const std::string& command);
  
    /*
    void addDevelopmentCard(std::unique_ptr<DevelopmentCard> card);
    void useDevelopmentCard(const std::string& command);
    void buyDevelopmentCard();
    const std::vector<std::unique_ptr<DevelopmentCard>>& getDevelopmentCards() const;
    */


};

#endif // PLAYER_HPP
