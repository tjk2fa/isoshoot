//
// Created by Tom on 1/8/20.
//

#include <iostream>
#include "Entity.h"
#include "gameMap.h"



Entity::Entity(int x, int y, float tileSize){
    worldX = x;
    worldY = y;
    texCoords = sf::IntRect();

    //std::cout << "entity at: " << x << y << std::endl;
    worldCoords = std::vector<sf::IntRect>();
    worldCoords.push_back(sf::IntRect(x+tileSize/2.f,y-tileSize/2.f,0,0));
}


//Really need to make this less crappy somehow
Wall::Wall(direction d, int x, int y, float tileSize) : Entity(x, y, tileSize){
    dir = d;
    if(d==north) {
        //worldX = xthTile * tileSize,
        //i * tileSize,
        texCoords.left = (75 + 2 * wallSpriteWidth);
        texCoords.top = 0;
        texCoords.width = wallSpriteWidth;
        texCoords.height = wallSpriteHeight;
        worldCoords[0].width += tileSize;
        worldCoords[0].height +=tileSize/3.f;
    }
    else if(d==south) {
        texCoords.left = (75 + wallSpriteWidth);
        texCoords.top = 0;
        texCoords.width = wallSpriteWidth;
        texCoords.height = wallSpriteHeight;
        worldCoords[0].top += tileSize*2.f/3.f;
        worldCoords[0].width = tileSize;
        worldCoords[0].height = tileSize/3.f;

    }
    else if(d==east){
        texCoords.left = (75+3*wallSpriteWidth);
        texCoords.top = 0;
        texCoords.width = wallSpriteWidth;
        texCoords.height = wallSpriteHeight;
        worldCoords[0].left += tileSize*2.f/3.f;
        worldCoords[0].width += tileSize/3.f;
        worldCoords[0].height += tileSize;

    }
    else if(d==west) {
        texCoords.left = 75;
        texCoords.top = 0;
        texCoords.width = wallSpriteWidth;
        texCoords.height = wallSpriteHeight;
        worldCoords[0].width += tileSize/3.f;
        worldCoords[0].height += tileSize;
    }
    else if (d==southeast) {
        texCoords.left = 444;
        texCoords.top = 0;
        texCoords.width = 73;
        texCoords.height = 115;
        worldCoords[0].left += tileSize*2.f/3.f;
        worldCoords[0].width += tileSize/3.f;
        worldCoords[0].height += tileSize;
        worldCoords.push_back(sf::IntRect(x+tileSize/2.f,y-tileSize/2.f,0,0));
        worldCoords[1].top += tileSize*2.f/3.f;
        worldCoords[1].width += tileSize;
        worldCoords[1].height += tileSize/3.f;


    }
    else if (d==northwest) {
        texCoords.left = 517;
        texCoords.top = 0;
        texCoords.width = 73;
        texCoords.height = 115;
        worldCoords[0].width += tileSize;
        worldCoords[0].height +=tileSize/3.f;
        worldCoords.push_back(sf::IntRect(x+tileSize/2.f,y-tileSize/2.f,0,0));
        worldCoords[1].width += tileSize/3.f;
        worldCoords[1].height += tileSize;

    }
    else if (d==southwest) {
        texCoords.left = 590;
        texCoords.top = 0;
        texCoords.width = 49;
        texCoords.height = 127;
        worldCoords[0].top += tileSize*2.f/3.f;
        worldCoords[0].width = tileSize;
        worldCoords[0].height = tileSize/3.f;
        worldCoords.push_back(sf::IntRect(x+tileSize/2.f,y-tileSize/2.f,0,0));
        worldCoords[1].width += tileSize/3.f;
        worldCoords[1].height += tileSize;
    }
    else if (d==northeast){
        texCoords.left = 638;
        texCoords.top = 0;
        texCoords.width = 49;
        texCoords.height = 127;
        worldCoords[0].width += tileSize;
        worldCoords[0].height +=tileSize/3.f;
        worldCoords.push_back(sf::IntRect(x+tileSize/2.f,y-tileSize/2.f,0,0));
        worldCoords[1].left += tileSize*2.f/3.f;
        worldCoords[1].width += tileSize/3.f;
        worldCoords[1].height += tileSize;

    }



    zHeight = 90;
}

activeEntity::activeEntity(activeEntType d, int x, int y, float tileSize) : Entity(x, y, tileSize) {
    if(d == player){
        texCoords.left = 0;
        texCoords.top = 39;
        texCoords.width = 70;
        texCoords.height = 75;
        zHeight = 41;
        worldCoords[0].width = tileSize;
        worldCoords[0].width = tileSize;
    }
    moving = false;
    dir = southeast;
    type = d;


}
