#ifndef DEVELOPMENT_CARD_HPP
#define DEVELOPMENT_CARD_HPP

#include <string>
#include "Tile.hpp"
#include "Player.hpp"

class Catan;
extern Catan* globalCatan;

class DevelopmentCard {
public:
    virtual ~DevelopmentCard() {}
    virtual std::string getType() const = 0;
    // This is a pure virtual function, meaning that it must be implemented by any derived class
    virtual void applyBenefit(Player* player, const std::variant<std::vector<ResourceType>, std::pair<int, int>>& benefit) = 0;
protected:    
    map<ResourceType, int> cost = { {ResourceType::ORE, 1}, {ResourceType::WHEAT, 1}, {ResourceType::SHEEP, 1} };
};



class MonopolyCard : public DevelopmentCard {
public:
    MonopolyCard() = default;
    std::string getType() const override;
    void applyBenefit(Player* player, const std::variant<vector<ResourceType>, std::pair<int, int>>& benefit) override;
};

class RoadBuildingCard : public DevelopmentCard {
public:
    RoadBuildingCard() = default;
    std::string getType() const override;
    void applyBenefit(Player* player, const std::variant<vector<ResourceType>, std::pair<int, int>>& benefit) override;
};

class YearOfPlentyCard : public DevelopmentCard {
public:
    YearOfPlentyCard() = default;
    std::string getType() const override;
    void applyBenefit(Player* player, const std::variant<vector<ResourceType>, std::pair<int, int>>& benefit) override;
};

class KnightCard : public DevelopmentCard {
public:
    KnightCard() = default;
    std::string getType() const override;
    void applyBenefit(Player* player, const std::variant<vector<ResourceType>, std::pair<int, int>>& benefit) override;
};

class VictoryPointCard : public DevelopmentCard {
public:
    VictoryPointCard() = default;
    std::string getType() const override;
    void applyBenefit(Player* player, const std::variant<vector<ResourceType>, std::pair<int, int>>& benefit) override;
};

// Function to create a random development card
DevelopmentCard* createRandomDevelopmentCard();

#endif // DEVELOPMENT_CARD_HPP
