#include "Player.hpp"
#include <vector>


Player::Player(const string &name, Board& board) :   knightCount(0), victoryPoints(0), board(board), name(name), points(0), Citys(0) {
    for (int i = WOOD; i <= ORE; ++i) {
        resources[static_cast<ResourceType>(i)] = 100;
    }
    
}

void Player::status() const {
    cout << "This is the status of: " << getName() << endl;
    cout << "Points: " << getPoints() << endl;
    cout << "Number of Cities: " << getNumOfCity() << endl;
    cout << "Number of Settlements: " << settlements.size() << endl;
    // cout << "Number of Development Cards: " << getDevelopmentCards().size() << endl;
    // cout << "Number of Knights: " << getKnightCount() << endl;
    // cout << "Number of Victory Points: " << victoryPoints << endl;
    // cout << "Number of Roads: " << getNumOfRoads() << endl;
    cout << "Resources:" << endl;
    for (const auto& resource : getResources()) {
        cout << "  " << resourceTypeToString(resource.first) << ": " << resource.second << endl;
    }
    // cout << "the development cards are: " << endl;
    // for (const auto& card : getDevelopmentCards()) {
    //     cout << "  " << card->getType() << endl;
    // }

}

void Player::Buy(BuyType type) {
    // There is no problem creating a map with each call
    // to the function because the local object cost is created
    // on the stack and automatically deleted at the end of the function.
    map<ResourceType, int> cost;

    switch (type) {
        case ROAD:
            cost = {{WOOD, 1}, {BRICK, 1}};
            break;
        case SETTLEMENT:
            cost = {{WOOD, 1}, {BRICK, 1}, {SHEEP, 1}, {WHEAT, 1}};
            break;
        case CITY:
            cost = {{WHEAT, 2}, {ORE, 3}};
            break;
        case DEVELOPMENT_CARD:
            cost = {{ORE, 1}, {WHEAT, 1}, {SHEEP, 1}};
            break;
        default:
            cout << "Unknown purchase type." << endl;
            return;
    }

    if (checkResources(cost)) {
        // Deduct resources using removeResource
        try {
            for (const auto& item : cost) {
                removeResource(item.first, item.second);
            }
            cout << "Purchase of " << resourceTypeToString(cost.begin()->first) << " successful." << endl;
        } catch (const runtime_error& e) {
            cout << e.what() << endl;
        }
    }
    else {
        cout << "Not enough resources to complete the purchase." << endl;

    }
}

bool Player::checkResources(const map<ResourceType, int>& cost) {
    bool hasAllResources = true;
    for (const auto& item : cost) {
        if (resources[item.first] < item.second) {
            hasAllResources = false;
            cout << "Resource: " << resourceTypeToString(item.first) 
                      << ", Required: " << item.second 
                      << ", Available: " << resources[item.first] << endl;
        }
    }

    return hasAllResources;
}

string Player::resourceTypeToString(ResourceType type) const {
    switch(type) {
        case WOOD: return "Wood";
        case BRICK: return "Brick";
        case SHEEP: return "Sheep";
        case WHEAT: return "Wheat";
        case ORE: return "Ore";
        default: return "Unknown";
    }
}

ResourceType Player::stringToResourceType(const std::string& str) const {
    if (str == "Wood") {
        return WOOD;
    } else if (str == "Brick") {
        return BRICK;
    } else if (str == "Sheep") {
        return SHEEP;
    } else if (str == "Wheat") {
        return WHEAT;
    } else if (str == "Ore") {
        return ORE;
    } else {
        throw std::runtime_error("Invalid resource type.");
    }
}

void Player::placeSettlement(int vertexIndex) {

    /* Validator object explanation:
        We create a validator object to check
        if the player can place a settlement on the vertex
        the validator object will check all
        the conditions and return a boolean value if the player can place a settlement 
    */
   Validator validator("Player", "placeSettlement", this, vertexIndex, board);
    if (!validator.isValid()) {
        return;
    }   
    // Get the vertex object from the map of vertices for 
    Vertex& vertex = board.vertices.at(vertexIndex); // Using at() instead of []

    // Condition to check if this is the first 2 settelments of the player
    // that the player dont need to buy the settlement because he gets it for free
   
    // If this is not the start of the game
    if(this->getPoints() > 2){
         Buy(Player::BuyType::SETTLEMENT);
    }
    // If this is the start of the game
    else{
        // Get the tiles that are associated with the vertex that we built the settlement on
        vector<Tile*> tilesForThisVertex = board.getTilesForVertex(vertexIndex);
        // Iterate over the tiles and add the resources to the player
        for (Tile* tile : tilesForThisVertex) {
            addResource(tile->getResource(), 1);
        }
    }
    vertex.setVertexProperties(Vertex::VertexType::SETTLEMENT, this);
    this->settlements.push_back(vertexIndex); // Add the settlement to the player's list of settlements
    this -> incrementPoints(); // Settlement is worth 1 point
    cout << "Player " << getName() << " increment points to " << getPoints() << endl;
    cout << name << " placed a settlement on vertex " << vertexIndex << endl;
}


void Player::placeRoad(int roadIndex) { 
    Validator validator("Player", "placeRoad", this, roadIndex, board);
    if (!validator.isValid()) {
        return;
    }   
    Road& road = board.roads.at(roadIndex);


    // adding a if condition to check if the player has a RoadBuilding card in his hand
    // if this is the case, the player can place two roads without the need to buy them.
    if (getUsingRoadBuildingCard()) {
        road.setPlayer(this); // Set the player of the road to the current player
        cout << name << " placed a road on road " << roadIndex << endl;
        return;
    } 
    if(this->getPoints() > 2){
        Buy(Player::BuyType::ROAD);
    }
    

    road.setPlayer(this); // Set the player of the road to the current player
    cout << name << " placed a road on road " << roadIndex << endl;
}

/* Explanation of the function upgradeSettlementToCity:

    This function performs the following actions:
    1. Validates if the player can upgrade a settlement to a city using the Validator object.
    2. If the validation fails, the function exits without making any changes.
    3. If validation is successful, retrieves the Vertex object from the board using the provided vertexIndex.
    4. Initiates the process of purchasing a city by calling the Buy method with the appropriate BuyType.
    5. Changes the type of the specified vertex to CITY.
    6. Increments the player's number of cities.
    7. Increases the player's points.
    8. Outputs a message indicating the successful upgrade of a settlement to a city.
*/
void Player::upgradeSettlementToCity(int vertexIndex) {
    Validator validator("Player", "upgradeSettlementToCity", this, vertexIndex, board);
    if (!validator.isValid()) {
        return;
    }  
    Vertex& vertex = board.vertices.at(vertexIndex);
    if (this->getPoints() > 1) {
        Buy(Player::BuyType::CITY);
    }
    else{
        cout << "You in the start of the game, you can't buy a city" << endl;
        return;
    }
   
    decrementNumOfSettlements(vertexIndex);
    // vertex.setType(Vertex::VertexType::CITY);
    vertex.setVertexProperties(Vertex::VertexType::CITY, this);
    this->incrementNumOfCity();
    this->incrementPoints();
    std::cout << "Player " << name << " upgraded a settlement to a city on vertex " << vertexIndex << std::endl;
}

void Player::Trade(Player& player, ResourceType give, int giveAmount, ResourceType take, int takeAmount) {
    // check if the player has the resources to trade
    std::map<ResourceType, int> cost = { {give, giveAmount} };
    if (!checkResources(cost)) {
        throw std::runtime_error("Not enough resources to trade.");
    }

    // remove the resources from the player
    this->removeResource(give, giveAmount);

    // add the resources to the other player
    player.addResource(give, giveAmount);

    // remove the resources from the other player
    player.removeResource(take, takeAmount);

    // add the resources to the player
    this->addResource(take, takeAmount);
}

void Player::addResource(ResourceType resource, int amount) {
    resources[resource] += amount;
}

void Player::removeResource(ResourceType resource, int amount) {
    if (resources[resource] >= amount) {
        resources[resource] -= amount;
    } else {
        throw std::runtime_error("Not enough resources");
    }
}

int Player::getPoints() const {
    return points;
}

int Player::getNumOfCity() const {
    return Citys;
}

void Player::incrementNumOfCity() {
    Citys++;
}

void Player::incrementPoints() {
    points++;
}

string Player::getName() const {
    return name;
}

int Player::getNumOfSettlements() const {
    return settlements.size();
}
// Getter for resources
map<ResourceType, int> Player::getResources() const {
    return resources;
}



void Player::incrementKnightCount() {
    knightCount++;
}

int Player::getKnightCount() const {
    return knightCount;
}

bool Player::getUsingRoadBuildingCard() const {
    return usingRoadBuildingCard;
}

void Player::setUsingRoadBuildingCard(bool value) {
    usingRoadBuildingCard = value;
}

int Player::getNumOfRoads() const {
// loop over all the roads and search for the roads that belong to the player
    int count = 0;
    for (const auto& road : board.getRoads()) {
        if (road.getPlayerName() == this->getName()) {
            count++;
        }
    }
    return count;

}

void Player::incrementVictoryPoints() {
        victoryPoints++;
}

/* Explanation of the function decrementNumOfSettlements:

    This function performs the following actions:
    1. Searches for the vertexIndex in the player's list of settlements.
    2. If the vertexIndex is found, removes the vertexIndex from the list of settlements.
    3. If the vertexIndex is not found, the function does nothing.
*/
void Player::decrementNumOfSettlements(int vertexIndex) {
    auto it = std::find(settlements.begin(), settlements.end(), vertexIndex);
    if (it != settlements.end()) {
        settlements.erase(it);
    }
}

// Getter for development cards of the player
const std::vector<std::unique_ptr<DevelopmentCard>>& Player::getDevelopmentCards() const {
    return developmentCards;    
}

void Player::buyDevelopmentCard() {
    // check if the player is not on the begin of the game
    // Check if the player has enough resources to buy a development card using method Buy
    Buy(Player::BuyType::DEVELOPMENT_CARD);
    auto& deck = board.getDeck();
    if (deck.empty()) {
        std::cerr << "No more development cards available." << std::endl;
        return;
    }
    // Add the card to the player's hand in random order
    addDevelopmentCard(std::move(deck.back()));
    deck.pop_back();
}

void Player::addDevelopmentCard(std::unique_ptr<DevelopmentCard> card) {
    // if condition to check if the card is victory point
    // if this is the case, use the methos useDevelopmentCard and insert 
    // the command "VictoryPoint" to implement the victory point through the method.
    if (card->getType() == "VictoryPoint") {
        developmentCards.push_back(std::move(card));
        useDevelopmentCard("VictoryPoint");
        return;
    }else{
        developmentCards.push_back(std::move(card));
    }
}

void Player::useDevelopmentCard(const std::string& command) {
    // add check if the parameters are valid - is string
    
    // Breaks the string into words (tokens) using a default separator (space).
    std::istringstream iss(command);
    std::vector<std::string> tokens{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
    // If the player has no development cards, return
    if (tokens.empty()){
        cout << "No development cards available." << endl;
        return;
    }
    // The first token is the type of the card
    std::string cardType = tokens[0];
    // Find the card in the player's hand
    auto it = std::find_if(developmentCards.begin(), developmentCards.end(),
        [&cardType](const std::unique_ptr<DevelopmentCard>& card) {
            return card->getType() == cardType;
        }); 
    // If the card is not found, print an error message and return
    if (it == developmentCards.end()) {
        cout << "No such card available." << endl;
        return;
    }
    // If the card type is "Monopoly" and there are two parameters in the command.
    if (cardType == "Monopoly" && tokens.size() == 2) {
        try {
        ResourceType resource = stringToResourceType(tokens[1]);
        (*it)->applyBenefit(this, std::vector<ResourceType>{resource});
    } catch(const std::exception& e) {
        std::cerr << "The resource specified in the command does not exist." << std::endl;
    }
        // Turn on the monopoly card


       
    } else if (cardType == "YearOfPlenty" && tokens.size() >= 2 && tokens.size() <= 3) {
    try {
        std::vector<ResourceType> resources;
        for (size_t i = 1; i < tokens.size(); ++i) {
            resources.push_back(stringToResourceType(tokens[i]));
        }
        (*it)->applyBenefit(this, resources);
    } catch(const std::exception& e) {
        std::cerr << "The resource specified in the command does not exist." << std::endl;
    }
}
    else if (cardType == "RoadBuilding" && tokens.size() == 3) {
        try {
            setUsingRoadBuildingCard(true);
            cout << "Road Building card" << endl;
            int roadIndex1 = std::stoi(tokens[1]);
            int roadIndex2 = std::stoi(tokens[2]);
            cout << "Road 1: " << roadIndex1 << " Road 2: " << roadIndex2 << endl;


            (*it)->applyBenefit(this, std::make_pair(roadIndex1, roadIndex2));
        } catch(const std::exception& e) {
            std::cout << "Invalid road indices specified in the command." << std::endl;
        }
    } else if (cardType == "Knight") {
        (*it)->applyBenefit(this, std::make_pair(0, 0));
    } else if (cardType == "VictoryPoint") {
        (*it)->applyBenefit(this, std::make_pair(0, 0));
    } else {
        std::cerr << "Invalid command format." << std::endl;
        return;
    }
    setUsingRoadBuildingCard(false);

    developmentCards.erase(it);
}







