//
// Created by Tom on 1/8/20.
//

#include <iostream>
#include "Entity.h"
Entity::Entity(int x, int y){
    worldX = x;
    worldY = y;
}

Wall::Wall(direction d, int x, int y) : Entity(x, y){
    dir = d;
    this->texCoords = sf::IntRect();
    if(d==north) {
        texCoords.left = (75 + 2 * wallSpriteWidth);
        texCoords.top = 0;
        texCoords.width = wallSpriteWidth;
        texCoords.height = wallSpriteHeight;
    }
    else if(d==south) {
        texCoords.left = (75 + wallSpriteWidth);
        texCoords.top = 0;
        texCoords.width = wallSpriteWidth;
        texCoords.height = wallSpriteHeight;
    }
    else if(d==east){
         texCoords.left = (75+3*wallSpriteWidth);
         texCoords.top = 0;
        texCoords.width = wallSpriteWidth;
        texCoords.height = wallSpriteHeight;
    }
    else if(d==west) {
        texCoords.left = 75;
        texCoords.top = 0;
        texCoords.width = wallSpriteWidth;
        texCoords.height = wallSpriteHeight;
    }
    else if (d==southeast) {
        texCoords.left = 444;
        texCoords.top = 0;
        texCoords.width = 73;
        texCoords.height = 115;
    }
    else if (d==northwest) {
        texCoords.left = 444+73;
        texCoords.top = 0;
        texCoords.width = 73;
        texCoords.height = 115;
    }
    else if (d==southwest) {
        texCoords.left = 444+73*2;
        texCoords.top = 0;
        texCoords.width = 49;
        texCoords.height = 127;
    }
    else if (d==northeast){
        texCoords.left = 638;
        texCoords.top = 0;
        texCoords.width = 49;
        texCoords.height = 127;
    }



    zHeight = 90;
}