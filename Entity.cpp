//
// Created by Tom on 1/8/20.
//

#include "Entity.h"
Entity::Entity(int x, int y, sf::Sprite& s) : sprite(s){
    worldX = x;
    worldY = y;
}

Wall::Wall(direction d, int x, int y, sf::Sprite& s) : Entity(x, y, s){
    dir = d;
}