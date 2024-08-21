#include "DevelopmentCard.hpp"
#include <cstdlib> // for rand()
#include "catan.hpp"
#include "Player.hpp"


std::string MonopolyCard::getType() const {
    return "Monopoly";
}

/* Explanation of the applyBenefit method in MonopolyCard:

 * The applyBenefit method is responsible for executing the effect of the Monopoly card.
 * This card allows the player who played it to take all resources of a specific type 
 * from all other players in the game. 
 * 
 * The method first checks if the benefit parameter is a vector of ResourceType.
 * If not, it throws an invalid_argument exception, as MonopolyCard only operates on resources.
 * 
 * It then extracts the resource type from the vector and gathers all players in the game.
 * The method filters out the player who played the card, since they are the one collecting resources.
 * 
 * The method iterates over all other players, retrieves the amount of the specified resource they have,
 * and transfers that amount to the player who played the Monopoly card using the Trade method.
 */
void MonopolyCard::applyBenefit(Player* player, const std::variant<vector<ResourceType>, std::pair<int, int>>& benefit) {
    if (!std::holds_alternative<std::vector<ResourceType>>(benefit)) {
        throw std::invalid_argument("Invalid argument for MonopolyCard");
    }
    ResourceType MonopolResources = std::get<std::vector<ResourceType>>(benefit)[0];
    std::vector<Player*> allPlayers = globalCatan->getPlayers();
    std::vector<Player*> TargetPlayers;
    for (Player* currentplayer : allPlayers) {
        if (currentplayer->getName() != player->getName()) {
            TargetPlayers.push_back(currentplayer);
        }
    }
    for (Player* targetplayer : TargetPlayers) {
        auto TargetResource = targetplayer->getResources(); 
        int amount = TargetResource.at(MonopolResources);
        targetplayer->Trade(*player, MonopolResources, amount, MonopolResources, 0);
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

/* Explanation of the applyBenefit method in YearOfPlentyCard:
 * 
 * The applyBenefit method is responsible for executing the effect of the Year of Plenty card.
 * This card allows the player to choose two different resources from the bank.
 * 
 * The method first checks if the benefit parameter is a vector of ResourceType.
 * If not, it throws an invalid_argument exception, as YearOfPlentyCard only operates on resources.
 * 
 * It then extracts the vector of resources from the benefit parameter.
 * The method iterates over the resources in the vector and adds one unit of each resource 
 * to the player's inventory using the addResource method.
 */
void YearOfPlentyCard::applyBenefit(Player* player, const std::variant<vector<ResourceType>, std::pair<int, int>>& benefit) {
    if (!std::holds_alternative<std::vector<ResourceType>>(benefit)) {
            throw std::invalid_argument("Invalid argument for YearOfPlentyCard");
        }
        const std::vector<ResourceType>& YearOfPlentyResources = std::get<std::vector<ResourceType>>(benefit);
        for (ResourceType resource : YearOfPlentyResources) {
            player->addResource(resource, 1); 
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

