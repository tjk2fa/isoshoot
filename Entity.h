//
// Created by Tom on 1/8/20.
//

#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H
#include "SFML/Graphics.hpp"

class gameMap;
class mapTile;




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
    player,
    zombie,
    bullet,
};

class Entity{
public:
    //mapTile* map;
    int zHeight;
    int worldX; //location to render entity
    int worldY; //location to render entity
    std::vector<sf::IntRect> worldCoords; //vector of rectangles for collisions
    sf::IntRect texCoords; //where the ent is on the sprite sheet


    Entity(int x, int y, float tileSize);

};

struct Wall : Entity{
    direction dir;
    const int wallSpriteWidth = 49;
    const int wallSpriteHeight = 114;
    Wall(direction d, int x, int y, float tileSize);
};


struct activeEntity : Entity {

    mapTile* map;
    direction dir;
    activeEntType type;
    bool moving;
    activeEntity(activeEntType d, int x, int y, float tileSize);

};


#endif //GAME_ENTITY_H
