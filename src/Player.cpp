#include "Player.hpp"
#include "Tile.hpp"
#include "catan.hpp"
#include <vector>
#include <utility>
using std::istream_iterator;
using std::find_if;
using std::exception;
using std::cerr;
using std::stoi;
using std::make_pair;
using std::move;
using std::count;



Player::Player(const string &name, Board& board) :   knightCount(0), victoryPoints(0), board(board), name(name), points(0), Citys(0) {
    for (int i = WOOD; i <= ORE; ++i) {
        resources[static_cast<ResourceType>(i)] = 10;
    }

}

void Player::status() const {
    cout << "This is the status of: " << getName() << endl;
    cout << "Points: " << getPoints() << endl;
    cout << "Number of Cities: " << getNumOfCity() << endl;
    cout << "Number of Settlements: " << settlements.size() << endl;
    cout << "Number of Development Cards: " << developmentCards.size() << endl;
    cout << "Number of Knights: " << getKnightCount() << endl;
    cout << "Number of Victory Points: " << victoryPoints << endl;
    cout << "Number of Roads: " << getNumOfRoads() << endl;

    // print the resources of the player
    cout << "Resources:" << endl;
    for (const auto& resource : getResources()) {
        cout << "  " << resourceTypeToString(resource.first) << ": " << resource.second << endl;
    }

    // print if this  is player turn or not, 
    // add if i want and have a time that check that: and if not, print the name of the player that is playing
    // if (isMyTurn) {
    //     cout << "It is your turn" << endl;
    // } 

    // print the development cards that the player has
    printDevelopmentCards();
}

void Player::Buy(BuyType type) {
    // There is no problem creating a map with each call
    // to the function because the local object cost is created
    // on the stack and automatically deleted at the end of the function.
    map<ResourceType, int> cost;
    string purchaseType;

    switch (type) {
        case ROAD:
            cost = {{WOOD, 1}, {BRICK, 1}};
            purchaseType = "Road";
            break;
        case SETTLEMENT:
            cost = {{WOOD, 1}, {BRICK, 1}, {SHEEP, 1}, {WHEAT, 1}};
            purchaseType = "Settlement";
            break;
        case CITY:
            cost = {{WHEAT, 2}, {ORE, 3}};
            purchaseType = "City";
            break;
        case DEVELOPMENT_CARD:
            cost = {{ORE, 1}, {WHEAT, 1}, {SHEEP, 1}};
            purchaseType = "Development Card";
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
            // print the purchase was successful of what the player bought
            cout << "Purchase of " << purchaseType << " successful." << endl;
        } catch (const runtime_error& e) {
            cout << e.what() << endl;
            #ifdef RUNNING_TESTS
                throw;  // rethrow the exception for testing purposes
            #else
                handleError(e);  // handle the error in the normal program flow
                
            #endif 
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

void Player::handleError(const std::exception& e) {
        // handle the error in the normal program flow
        std::cerr << "Handled error: " << e.what() << std::endl;
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

ResourceType Player::stringToResourceType(const string& str) const {
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
        throw runtime_error("Invalid resource type.");
    }
}

void Player::placeSettlement(int vertexIndex) {

    /* Validator object explanation:
        We create a validator object to check
        if the player can place a settlement on the vertex
        the validator object will check all
        the conditions and return a boolean value if the player can place a settlement 
    */
    Validator validator("Player", "placeSettlement", this, vertexIndex, board, ResourceType::WOOD, 0, ResourceType::BRICK, 0, nullptr);
    if (!validator.isValid()) {
        return;
    }   
    // Get the vertex object from the map of vertices for 
    Vertex& vertex = board.vertices.at(vertexIndex); // Using at() instead of []
    // If this is not the start of the game
    if (this->getRoundStatus()[2]) {
        // Check if the player has enough resources to buy a settlement
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
    cout << "Player " << getName() << " incremented points to " << getPoints() << " and placed a settlement on vertex " << vertexIndex << endl;

}

void Player::placeRoad(int roadIndex) { 
    Validator validator("Player", "placeRoad", this, roadIndex, board, ResourceType::WOOD, 0, ResourceType::BRICK, 0, nullptr);
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
    if (this->getRoundStatus()[2]) {
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
    Validator validator("Player", "upgradeSettlementToCity", this, vertexIndex, board, ResourceType::WOOD, 0, ResourceType::BRICK, 0, nullptr);
    if (!validator.isValid()) {
        return;
    }  
    Vertex& vertex = board.vertices.at(vertexIndex);
    // we already checked if this is the start of the game in the validator
    // if this is the start of the game the validator will return false and the function will not reach this point
    Buy(Player::BuyType::CITY);
    
    decrementNumOfSettlements(vertexIndex);
    // vertex.setType(Vertex::VertexType::CITY);
    vertex.setVertexProperties(Vertex::VertexType::CITY, this);
    this->incrementNumOfCity();
    this->incrementPoints();
    cout << "The player " << name << " upgraded a settlement to a city on vertex " << vertexIndex << endl;
}


/* Explanation of the function Trade:

    This function performs the following actions:
    1. Validates if the player can trade resources with another player using the Validator object.
    2. If the validation fails, the function exits without making any changes.
    3. If validation is successful, removes the specified amount of resources from the current player.
    4. Adds the specified amount of resources to the other player.
    5. Removes the specified amount of resources from the other player.
    6. Adds the specified amount of resources to the current player.
*/
void Player::Trade(Player& player, ResourceType give, int giveAmount, ResourceType take, int takeAmount) {
    Validator validator("Player", "Trade", this, 0, board, give, giveAmount, take, takeAmount, &player);
    if (!validator.isValid()) {
        return;
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
        throw runtime_error("Not enough resources");
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
    Catan::checkWinner();
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

vector<int> Player::getSettlements() const {
    return settlements;
}

void Player::setUsingRoadBuildingCard(bool value) {
    usingRoadBuildingCard = value;
}



void Player::setisMyTurn(bool value) {
    isMyTurn = value;
}

// This function made because the player can't use a development card that was purchased this turn
void Player::setPurchaseDevelopmentCardThisTurn(bool value) {
    parchaseDevelopmentCardThisTurn = value;
}

void Player::setRoundStatus(const vector<bool>& newStatus) {
    // Validate the size of the input vector
    if (newStatus.size() != 3) {
        throw std::invalid_argument("newStatus must have exactly 3 elements.");
    }
    // check if exactly one is true
    if(count(newStatus.begin(), newStatus.end(), true) != 1) {
        throw std::invalid_argument("Exactly one round must be true.");
    }
    roundStatus = newStatus;
}

vector<bool> Player::getRoundStatus() {
    return roundStatus;
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

int Player::getNumOfVictoryPoints() const {
    return victoryPoints;
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
    auto it = find(settlements.begin(), settlements.end(), vertexIndex);
    if (it != settlements.end()) {
        settlements.erase(it);
    }
}

/* Explanation of the function printDevelopmentCards:
    1. Checks if the player has any development cards.
    2. If the player has no development cards, outputs "No development cards".
    3. If the player has development cards, outputs the type of each development card and the number of each card.
*/
void Player::printDevelopmentCards() const {
    // Check if the player has any development cards
    if (developmentCards.size() == 0) {
        cout << "No development cards" << endl;
    }
    // If the player has development cards, print the type of each development card and the number of each card
    else {
        cout << "the development cards that " << name << " has:" << endl;
        map<string, int> cardCounts;
        for (const auto& card : developmentCards) {
            cardCounts[card->getType()]++;
        }
        for (const auto& card : cardCounts) {
            cout << card.first << ": " << card.second << endl;
        }
        cout << "Victory Points: " << victoryPoints << endl;
    }
}

void Player::setPurchaseYOPThisTurn(const vector<bool>& value) {
    purchaseYOPThisTurn = value;
}

vector<bool> Player::getPurchaseYOPThisTurn() const {
    return purchaseYOPThisTurn;
}

int Player::getNumOfDevelopmentCards() const {
    return developmentCards.size();
}   

const std::vector<std::unique_ptr<DevelopmentCard>>& Player::getDevelopmentCards() const {
    return developmentCards;
}


void Player::buyDevelopmentCard() {
    Validator validator("Player", "buyDevelopmentCard", this, -1, board, ResourceType::WOOD, 0, ResourceType::BRICK, 0, nullptr);
    if (!validator.isValid()) {
        return;
    }
    Buy(Player::BuyType::DEVELOPMENT_CARD);
    auto& deck = board.getDeck();
    // Add the card to the player's hand in random order
    addDevelopmentCard(std::move(deck.back()));
    // Remove the card from the deck for no one else to get it anymore
    deck.pop_back();
    setPurchaseDevelopmentCardThisTurn(true);
}

void Player::addDevelopmentCard(unique_ptr<DevelopmentCard> card) {
    // if condition to check if the card is victory point
    // if this is the case, use the methos useDevelopmentCard and insert 
    // the command "VictoryPoint" to implement the victory point through the method.
    if (card->getType() == "VictoryPoint" ){
        developmentCards.push_back(std::move(card));
        auto& lastCard = developmentCards.back();
        cout << "The Development Card you bought is: " << lastCard->getType() << endl;
        useDevelopmentCard("VictoryPoint");
        return;
    }
    if (card->getType() == "YearOfPlenty" ){
        vector<bool> temp = getPurchaseYOPThisTurn();
        if(temp[0] == true){
            setPurchaseYOPThisTurn({true, true});
        }
        else{
            setPurchaseYOPThisTurn({true, false});
        }
    }
    developmentCards.push_back(std::move(card));
    auto& lastCard = developmentCards.back();
    cout << "The Development Card you bought is: " << lastCard->getType() << endl;
}

void Player::useDevelopmentCard(const string& command) {
   
    // Breaks the string into words (tokens) using a default separator (space).
    // Used istringstream to easily parse and manipulate the string content into separate tokens.
    // Using istringstream helps to separate the words in a string very easily
    istringstream iss(command);
    vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};
    // The first token is the type of the card
    string cardType = tokens[0];
    // Find the card in the player's hand
    /* Explanation of the find the card in the player's hand:
    *  We use the find_if function to search for the development card in the player's hand.
    *  the find_if function takes the developmentCards vector as the first argument and the end of the vector as the second argument.
    *  The third argument is a lambda function that takes a development card as an argument and returns a boolean value based on the card type.
    *  The lambda function compares the card type with the cardType variable and returns true if they match.
    *  The it variable is an iterator that points to the development card in the player's hand.
    */
    auto it = find_if(developmentCards.begin(), developmentCards.end(),
        [&cardType](const unique_ptr<DevelopmentCard>& card) {
            return card->getType() == cardType;
        }); 

    // If the card is not found, print an error message and return
    if (it == developmentCards.end()) {
        cout << "No such card available." << endl;
        return;
    }
    // i hace to check if this is an YearOfPlenty card, because if it is, the player allowd to use it in the same turn.
    // hence, i have to set the purchaseDevelopmentCardThisTurn to false, and move the validator down for check the command.
    if (cardType == "YearOfPlenty" || cardType == "VictoryPoint") {
        setPurchaseDevelopmentCardThisTurn(false);
    }
    Validator validator("Player", "useDevelopmentCard", this, -1, board, ResourceType::WOOD, 0, ResourceType::BRICK, 0, nullptr);
    if (!validator.isValid()) {
        return;
    }   
    if (cardType == "Monopoly" && tokens.size() == 2) {
        try {
            
        ResourceType resource = stringToResourceType(tokens[1]);
        (*it)->applyBenefit(this, vector<ResourceType>{resource});
        } 
        catch(const exception& e) {
            cerr << "The resource specified in the command does not exist." << endl;
        #ifdef RUNNING_TESTS
                throw;  // rethrow the exception for testing purposes
            #else
                handleError(e);  // handle the error in the normal program flow
                
            #endif 
        }   
    } 
    else if (cardType == "YearOfPlenty" && tokens.size() >= 2 && tokens.size() <= 3) {
    try {
        vector<ResourceType> resources;
        for (size_t i = 1; i < tokens.size(); ++i) {
            resources.push_back(stringToResourceType(tokens[i]));
        }
        (*it)->applyBenefit(this, resources);
    } 
    catch(const exception& e) {
        cerr << "The resource specified in the command does not exist." << endl;
        #ifdef RUNNING_TESTS
                throw;  // rethrow the exception for testing purposes
            #else
                handleError(e);  // handle the error in the normal program flow
                
            #endif 
    }
    }
    else if (cardType == "RoadBuilding" && tokens.size() == 3) {
        try {
            setUsingRoadBuildingCard(true);
            int roadIndex1 = stoi(tokens[1]);
            int roadIndex2 = stoi(tokens[2]);
            cout << "Road 1: " << roadIndex1 << " Road 2: " << roadIndex2 << endl;
            (*it)->applyBenefit(this, make_pair(roadIndex1, roadIndex2));
        } catch(const exception& e) {
            cout << "Invalid road indices specified in the command." << endl;
            #ifdef RUNNING_TESTS
                throw;  // rethrow the exception for testing purposes
            #else
                handleError(e);  // handle the error in the normal program flow
                
            #endif 
        }
    } else if (cardType == "Knight") {
        (*it)->applyBenefit(this, make_pair(0, 0));
    } else if (cardType == "VictoryPoint") {
        // cout << "if the answer is 0, the player has not buy the card this turn. \nif the answer is 1 he did: " << parchaseDevelopmentCardThisTurn << endl;
        (*it)->applyBenefit(this, make_pair(0, 0));
    } else {
        cerr << "Invalid command format." << endl;
        return;
    }
    setUsingRoadBuildingCard(false);
    developmentCards.erase(it);
}







