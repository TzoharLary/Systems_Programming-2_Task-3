#ifndef ROAD_HPP
#define ROAD_HPP
#include <string>
using std::string;

class Player;

class Road {
public:
    int id;         // מזהה הדרך
    Player* player;     // השחקן שבנה את הדרך (0 אם לא תפוס)
    Road(int id);
    string getPlayerName() const;
    int getId() const;
};

#endif // ROAD_HPP
