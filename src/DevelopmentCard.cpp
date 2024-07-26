#include "DevelopmentCard.hpp"
#include <cstdlib> // for rand()
#include "catan.hpp"


std::string MonopolyCard::getType() const {
    return "Monopoly";
}

void MonopolyCard::applyBenefit(Player* player, ResourceType resource) {
    std::vector<Player*> allPlayers = globalCatan->getPlayers();
    // I isolate the players I want to take the resources from for a new vector
    std::vector<Player*> TargetPlayers;
    for (Player* currentplayer : allPlayers) {
        if (currentplayer->getName() != player->getName()) {
            TargetPlayers.push_back(currentplayer);
        }
    }
    // Loop through all target players 
    for (Player* targetplayer : TargetPlayers) {
        // i want to see all the resources of the player.
        // the resources variable is the map of the player resources
        auto TargetResource = targetplayer->getResources(); 
        // i storage the amount of the resource that i want to take in the variable amount
        int amount = TargetResource.at(resource);
        // I make a trade where I take all the resources
        // from the player who used the Monopoly card
        // and give him the amount of resources that I took
        // im take from the targetplayer the resource
        targetplayer->Trade(*player, resource, amount, resource, 0);
    }
}


std::string RoadBuildingCard::getType() const {
    return "Road Building";
}

void RoadBuildingCard::applyBenefit(Player* player, ResourceType resource) {

}

std::string YearOfPlentyCard::getType() const {
    return "Year of Plenty";
}

void YearOfPlentyCard::applyBenefit(Player* player, ResourceType resource) {
    // Logic for Year of Plenty benefit
}

std::string KnightCard::getType() const {
    return "Knight";
}

void KnightCard::applyBenefit(Player* player, ResourceType resource) {
    // Logic for Knight benefit
}

std::string VictoryPointCard::getType() const {
    return "Victory Point";
}

void VictoryPointCard::applyBenefit(Player* player, ResourceType resource) {
    // Logic for Victory Point benefit
}

DevelopmentCard* createRandomDevelopmentCard() {
    int cardType = rand() % 5; // Adjust based on actual probabilities
    switch (cardType) {
        case 0: return new MonopolyCard();
        case 1: return new RoadBuildingCard();
        case 2: return new YearOfPlentyCard();
        case 3: return new KnightCard();
        case 4: return new VictoryPointCard();
        default: return nullptr;
    }
}