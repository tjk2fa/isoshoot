//
// Created by Tom on 1/8/20.
//

#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H
#include "SFML/Graphics.hpp"

enum direction{
    north,
    south,
    east,
    west,
    northeast,
    southeast,
    southwest,
    northwest
};

enum activeEntType{
    zombie,
    bullet,
};

class Entity{
public:
    int worldX;
    int worldY;
    int zHeight;
    sf::IntRect texCoords;


    Entity(int x, int y);

};

struct Wall : Entity{
    direction dir;
    const int wallSpriteWidth = 49;
    const int wallSpriteHeight = 114;
    Wall(direction d, int x, int y);
};


class activeEntity : Entity{

    direction dir;
    activeEntType type;
    bool moving;




    activeEntity(direction d, activeEntType t);
};


#endif //GAME_ENTITY_H
