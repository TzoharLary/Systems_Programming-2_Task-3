#ifndef DEVELOPMENT_CARD_HPP
#define DEVELOPMENT_CARD_HPP

#include <string>
#include "Tile.hpp"
#include "Vertex.hpp"

/* Explanation of includes in DevelopmentCard.hpp:
*  We include the Tile.hpp because we want to use the ResourceType enum in the DevelopmentCard class.
*/

class Player;

class DevelopmentCard {
protected:

private:
    /*  This is a pure virtual function, meaning that it must be implemented by any derived class
        we do a virtual function because we want to be able to call this function on a different type of development card
        for example, the applyBenefit function of MonopolyCard would like to receive a vector of resource types, 
        while the applyBenefit function of RoadBuildingCard would like to receive a pair of road indices
    */ 
    virtual void applyBenefit(Player* player, const std::variant<std::vector<ResourceType>, std::pair<int, int>>& benefit) = 0;
    friend class Player;

public:
    virtual ~DevelopmentCard() {}
    virtual std::string getType() const = 0;

};



class MonopolyCard : public DevelopmentCard {
private:
    void applyBenefit(Player* player, const std::variant<vector<ResourceType>, std::pair<int, int>>& benefit) override;

public:
    MonopolyCard() = default;
    std::string getType() const override;
};

class RoadBuildingCard : public DevelopmentCard {
private:
    void applyBenefit(Player* player, const std::variant<vector<ResourceType>, std::pair<int, int>>& benefit) override;
public:
    RoadBuildingCard() = default;
    std::string getType() const override;
};



class KnightCard : public DevelopmentCard {
private:
    void applyBenefit(Player* player, const std::variant<vector<ResourceType>, std::pair<int, int>>& benefit) override;
public:
    KnightCard() = default;
    std::string getType() const override;
};



class VictoryPointCard : public DevelopmentCard {
private:
    void applyBenefit(Player* player, const std::variant<vector<ResourceType>, std::pair<int, int>>& benefit) override;
public:
    VictoryPointCard() = default;
    std::string getType() const override;
};

class YearOfPlentyCard : public DevelopmentCard {
private:
    void applyBenefit(Player* player, const std::variant<vector<ResourceType>, std::pair<int, int>>& benefit) override;
public:
    YearOfPlentyCard() = default;
    std::string getType() const override;
};


#endif // DEVELOPMENT_CARD_HPP
