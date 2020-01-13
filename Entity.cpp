//
// Created by Tom on 1/8/20.
//

#include "Entity.h"
Entity::Entity(int x, int y){
    worldX = x;
    worldY = y;
}

Wall::Wall(direction d, int x, int y) : Entity(x, y){
    dir = d;
    switch(d){
        case north:
            texCoords.left = 0;
            texCoords.top = 0;
        case south:
            texCoords.left = 0;
            texCoords.top = 0;
        case east:
            texCoords.left = 0;
            texCoords.top = 0;
        case west:
            texCoords.left = 0;
            texCoords.top = 0;
    }
    texCoords.width = wallSpriteWidth;
    texCoords.height = wallSpriteHeight;
    zHeight = 90;
}