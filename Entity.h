//
// Created by Tom on 1/8/20.
//

#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H
#include "SFML/Graphics.hpp"

class Entity{
private:
    int worldX;
    int worldY;
    sf::Sprite& sprite;
public:
    Entity(int x, int y, sf::Sprite& s);

};

struct Wall : Entity{
    enum direction{
        north,
        south,
        east,
        west
    };
    direction dir;
    Wall(direction d, int x, int y, sf::Sprite& s);
};

/*
struct activeEntity : Entity{
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
    enum type{
        human,
        zombie
    };
    sf::Vector2f velocity;
    activeEntity(direction d, type t);
};
 */
#endif //GAME_ENTITY_H
