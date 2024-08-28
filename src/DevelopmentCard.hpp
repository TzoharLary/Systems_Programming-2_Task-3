#ifndef DEVELOPMENT_CARD_HPP
#define DEVELOPMENT_CARD_HPP

#include <string>
#include "Tile.hpp"
#include "Vertex.hpp"
using std::variant;
using std::vector;
using std::pair;
using std::string;

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
    virtual void applyBenefit(Player* player, const variant<vector<ResourceType>, pair<int, int>>& benefit) = 0;
    friend class Player;

public:
    virtual ~DevelopmentCard() {}
    virtual string getType() const = 0;

};



class MonopolyCard : public DevelopmentCard {
private:
    void applyBenefit(Player* player, const variant<vector<ResourceType>, pair<int, int>>& benefit) override;

public:
    MonopolyCard() = default;
    string getType() const override;
};

class RoadBuildingCard : public DevelopmentCard {
private:
    void applyBenefit(Player* player, const variant<vector<ResourceType>, pair<int, int>>& benefit) override;
public:
    RoadBuildingCard() = default;
    string getType() const override;
};



class KnightCard : public DevelopmentCard {
private:
    void applyBenefit(Player* player, const variant<vector<ResourceType>, pair<int, int>>& benefit) override;
public:
    KnightCard() = default;
    string getType() const override;
};



class VictoryPointCard : public DevelopmentCard {
private:
    void applyBenefit(Player* player, const variant<vector<ResourceType>, pair<int, int>>& benefit) override;
public:
    VictoryPointCard() = default;
    string getType() const override;
};

class YearOfPlentyCard : public DevelopmentCard {
private:
    void applyBenefit(Player* player, const variant<vector<ResourceType>, pair<int, int>>& benefit) override;
public:
    YearOfPlentyCard() = default;
    string getType() const override;
};


#endif // DEVELOPMENT_CARD_HPP
