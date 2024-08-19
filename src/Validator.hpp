#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
using std::string;

class Player;
class Board;
class Road;
class Tile;
class Vertex;

class Validator {


private:
    string className;
    string functionName;
    void* obj;
    int index; // פרמטר נוסף לבדיקת אינדקס
    Board& board; // פרמטר נוסף לבדיקת לוח
    bool valid;
    void validate();

    friend class Board;
    /*
    void validateBoard();
    void validateRoad();
    void validateTile();
    void validateVertex();
    */
public:
    Validator(const string& className, const string& functionName, void* obj, int index, Board& board);
    bool isValid() const;
    void validatePlayer();
        
};

#endif // VALIDATOR_H
