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
    }
    else if(d==south) {
        texCoords.left = (75 + wallSpriteWidth);
        texCoords.top = 0;
    }
     else if(d==east){
         texCoords.left = (75+3*wallSpriteWidth);
         texCoords.top = 0;
    }
      else if(d==west) {
        texCoords.left = 75;
        texCoords.top = 0;
    }



    texCoords.width = wallSpriteWidth;
    texCoords.height = wallSpriteHeight;
    zHeight = 90;
}