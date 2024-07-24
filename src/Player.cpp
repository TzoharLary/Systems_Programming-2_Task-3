#include "Player.hpp"
#include "Board.hpp"
#include "Validator.hpp"


Player::Player(const string &name) : name(name), points(0) {
    for (int i = WOOD; i <= ORE; ++i) {
        resources[static_cast<ResourceType>(i)] = 0;
    }
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
            cout << "Purchase successful!" << endl;
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

string Player::resourceTypeToString(ResourceType type) {
    switch(type) {
        case WOOD: return "Wood";
        case BRICK: return "Brick";
        case SHEEP: return "Sheep";
        case WHEAT: return "Wheat";
        case ORE: return "Ore";
        default: return "Unknown";
    }
}

void Player::placeSettlement(int vertexIndex, Board& board) {
    
    // Check if the vertexIndex is found in the map and exists
    if (board.vertices.find(vertexIndex) == board.vertices.end()) {
        throw out_of_range("Invalid vertex index");
    }

    // Check if the player has more than 5 settlements
    // Validator validator("Player", "placeSettlement", this);

    // if (settlements.size() >= 5) {
    //     throw std::runtime_error("You cannot have more than 5 settlements.");
    // }

    // Get the vertex object from the map
    Vertex& vertex = board.vertices.at(vertexIndex); // Using at() instead of []

    // check if the vertex is occupied by another player
    if (vertex.occupied) {
        throw runtime_error("There is already a settlement on this vertex");
    }

    /*   Check if there is a settlement on an adjacent vertex
         For loop that iterates over the adjacent vertices of the current vertex
         and checks if there is a settlement on any of them
    */ 
    for (int adjacentVertex : vertex.adjacentVertices) {
        if (board.vertices.at(adjacentVertex).occupied) { 
            throw runtime_error("There is a settlement on an adjacent vertex");
        }
    }

    if(this->getPoints() > 2){
         Buy(Player::BuyType::SETTLEMENT);
    }
    // i need to add resources to the player so i will check
    // the resource of the tile of the vertex using the getTilesForVertex method
    
    else{
        // Get the tiles that are associated with the vertex that we built the settlement on
        vector<Tile*> tilesForThisVertex = board.getTilesForVertex(vertexIndex);
        // Iterate over the tiles and add the resources to the player
        for (Tile* tile : tilesForThisVertex) {
            addResource(tile->getResource(), 1);
        }
    }

    vertex.occupied = true; // From now the vertex will be occupied by the player
    vertex.player = this; // Save the pointer to the player
    vertex.setType(Vertex::VertexType::SETTLEMENT); // Set the type of the vertex to a settlement
    this->settlements.push_back(vertexIndex); // Add the settlement to the player's list of settlements
    points += 1; // Settlement is worth 1 point
    cout << name << " placed a settlement on vertex " << vertexIndex << endl;
}

void Player::placeRoad(int roadIndex, Board& board) {
    // bool variable for know later if the index of the road is valid
    bool validRoad = false;

    if (roadIndex < 0 || roadIndex >= 72) {
    throw out_of_range("Invalid road index");
    }

    Road& road = board.roads.at(roadIndex);

    if (road.isOccupied()) {
        throw runtime_error("This road is already occupied by " + road.getPlayerName());
    }
    // TODO: add adjacent roads check for valid built road

    if(this->getPoints() > 2){
        Buy(Player::BuyType::ROAD);
    }
    // Road& road = board.roads.at(roadIndex);

    road.setPlayer(this);

    validRoad = true;

    if (!validRoad) {
        cout << "the road is not valid" << endl;
        throw out_of_range("Invalid road index");
    }

    cout << name << " placed a road on road " << roadIndex << endl;
}

void Player::upgradeSettlementToCity(int vertexIndex, Board& board) {
    // Check if the specified vertex index exists in the board's vertices map
    if (board.vertices.find(vertexIndex) == board.vertices.end()) {
        // If the vertex index does not exist, throw an out_of_range exception
        throw std::out_of_range("Invalid vertex index");
    }

    // Check if the player has more than 5 settlements
    if (Citys.size() >= 4) {
        throw std::runtime_error("You cannot have more than 5 settlements.");
    }
    
    // Access the vertex by index, assuming existence is already verified
    // because vertex is alias so we will get to the method with . and not ->
    Vertex& vertex = board.vertices.at(vertexIndex);

    // Check if the vertex is not occupied, if it's not owned by the current player, or if it's not a settlement
    if (!vertex.occupied || vertex.player != this || vertex.getType() == Vertex::VertexType::SETTLEMENT) {
        // If any condition is true, throw a runtime_error indicating the action cannot be performed
        throw std::runtime_error("You can only upgrade your own settlements to cities.");
    }

    // try to buy
    this->Buy(Player::BuyType::CITY);
    // Change the vertex type to CITY, indicating an upgrade
    vertex.setType(Vertex::VertexType::CITY);
    // Increment points by 1. This assumes a settlement is worth 1 point and upgrading to a city makes it worth 2 points in total
    points += 1;

    // Output a message indicating the player has upgraded a settlement to a city at the specified vertex
    std::cout << "Player " << name << " upgraded a settlement to a city on vertex " << vertexIndex << std::endl;
}

void Player::addResource(ResourceType resource, int amount) {
    resources[resource] += amount; 
}

void Player::removeResource(ResourceType resource, int amount) {
    if (resources[resource] >= amount) {
        resources[resource] -= amount;
        if (resources[resource] == 0) {
            resources.erase(resource);
        }
    } else {
        throw std::runtime_error("Not enough resources");
    }
}

string Player::getName() const {
    return name;
}

int Player::getPoints() const {
    return points;
}
