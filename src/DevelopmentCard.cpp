#include "DevelopmentCard.hpp"
#include <cstdlib> // for rand()
#include "catan.hpp"
#include "Player.hpp"


std::string MonopolyCard::getType() const {
    return "Monopoly";
}

void MonopolyCard::applyBenefit(Player* player, const std::variant<vector<ResourceType>, std::pair<int, int>>& benefit) {
  
    if (!std::holds_alternative<std::vector<ResourceType>>(benefit)) {
        throw std::invalid_argument("Invalid argument for MonopolyCard");
    }

    const std::vector<ResourceType>& resources = std::get<std::vector<ResourceType>>(benefit);
    if (resources.empty()) {
        throw std::invalid_argument("No resource provided for MonopolyCard");
    }
    ResourceType resource = resources[0]; 
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
    return "RoadBuilding";
}

void RoadBuildingCard::applyBenefit(Player* player, const std::variant<vector<ResourceType>, std::pair<int, int>>& benefit) {
    // Logic for Road Building benefit
    if (std::holds_alternative<std::pair<int, int>>(benefit)) {
            auto roads = std::get<std::pair<int, int>>(benefit);
            int roadIndex1 = roads.first;
            int roadIndex2 = roads.second;
            cout << "Road 1: " << roadIndex1 << " Road 2: " << roadIndex2 << endl;
            player->placeRoad(roadIndex1);
            player->placeRoad(roadIndex2);
    }
    else {
                throw std::invalid_argument("Invalid argument for RoadBuildingCard");
    }
}

std::string YearOfPlentyCard::getType() const {
    return "YearOfPlenty";
}

void YearOfPlentyCard::applyBenefit(Player* player, const std::variant<vector<ResourceType>, std::pair<int, int>>& benefit) {
    if (!std::holds_alternative<std::vector<ResourceType>>(benefit)) {
            throw std::invalid_argument("Invalid argument for YearOfPlentyCard");
        }

        const std::vector<ResourceType>& resources = std::get<std::vector<ResourceType>>(benefit);
        for (ResourceType resource : resources) {
            // לוגיקה להוספת המשאב לשחקן
            player->addResource(resource, 1); // דוגמה להוספת משאב לשחקן
        }

}

std::string KnightCard::getType() const {
    return "Knight";
}

void KnightCard::applyBenefit(Player* player, const std::variant<vector<ResourceType>, std::pair<int, int>>& benefit) {
    // Logic for Knight benefit
    player->incrementKnightCount();
    if (player->getKnightCount() == 3) {
        player->incrementPoints();
    }
}

std::string VictoryPointCard::getType() const {
    return "VictoryPoint";
}

void VictoryPointCard::applyBenefit(Player* player, const std::variant<vector<ResourceType>, std::pair<int, int>>& benefit) {
    player->incrementPoints();
    player->incrementVictoryPoints();
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