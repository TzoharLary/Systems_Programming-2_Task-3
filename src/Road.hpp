#ifndef ROAD_HPP
#define ROAD_HPP

class Player;

class Road {
public:
    int id;         // מזהה הדרך
    Player* player;     // השחקן שבנה את הדרך (0 אם לא תפוס)

    Road(int id) : id(id), player(nullptr) {}
};

#endif // ROAD_HPP
