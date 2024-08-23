#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include "Board.hpp"
using std::string;

class Player;
// class Board;
class Road;
class Tile;
class Vertex;

class Validator {

private:
    // fields:
    string className;
    string functionName;
    void* obj;
    int index; 
    Board& board; 
    bool valid;
    // The next 5 fields are used for the trade validation
    ResourceType giveResource;
    int giveAmount;
    ResourceType takeResource;
    int takeAmount;
    Player* otherPlayer;
    void validate(); // Validates objects based on their class type

    // The Board class need to access to method validatePlayer.
    friend class Board;
  
public:
    /* Constructor, isValid, and validatePlayer function with explanation:
    *  Constructor: Initializes the Validator object with the class name, function name, object, index, and board.
    *  isValid: Returns the value of the valid variable.
    *  validatePlayer: Validates the player methods.
    */
    Validator(const std::string& className, const std::string& functionName, void* obj, int index, Board& board, ResourceType giveResource = ResourceType::WOOD, int giveAmount = 0, ResourceType takeResource = ResourceType::BRICK, int takeAmount = 0, Player* otherPlayer = nullptr);
    bool isValid() const;
    void validatePlayer();
    /*
    void validateBoard();
    void validateRoad();
    void validateTile();
    void validateVertex();
    */
};

#endif // VALIDATOR_H
