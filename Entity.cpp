//
// Created by Tom on 1/8/20.
//

#include <iostream>
#include "Entity.h"
#include "gameMap.h"



Entity::Entity(){
    texCoords = sf::IntRect();
}



Floor::Floor(int x, int y){
    zHeight = 0;
    texCoords.top = 0;
    texCoords.left = 0;
    texCoords.height = 39;
    texCoords.width = 75;
}

/**Each if case contains the ent data for that direction of wall
 * worldX,Y = world coords for rendering
 * texCoords = location on sprite sheet
 * worldCoords = vector of world-space bounding boxes for collision detection
 */

//need to make this less crappy
Wall::Wall(direction d, int x, int y, float tileSize) : Entity(){
    dir = d;
    worldCoords = std::vector<sf::IntRect>();
    worldCoords.push_back(sf::IntRect(x*tileSize+tileSize/2.f,y*tileSize-tileSize/2.f,0,0));

    //west in map refers to north
    //east refers to south
    //north refers to east
    //south refers to west


    if(d==west) {
        worldX = x*tileSize;
        worldY = y*tileSize;
        texCoords.left = 173;
        texCoords.top = 0;
        texCoords.width = 49;
        texCoords.height = 114;
        worldCoords[0].width += tileSize;
        worldCoords[0].height +=tileSize/3.f;
    }
    else if(d==east) {
        worldX = x*tileSize + 2.f*tileSize/3.f;
        worldY = y*tileSize;
        texCoords.left = 124;
        texCoords.top = 0;
        texCoords.width = 49;
        texCoords.height = 114;
        worldCoords[0].top += tileSize*2.f/3.f;
        worldCoords[0].width = tileSize;
        worldCoords[0].height = tileSize/3.f;

    }
    else if(d==north){
        worldX = x*tileSize + tileSize/3.f;
        worldY = y*tileSize - tileSize/3.f;
        texCoords.left = 222;
        texCoords.top = 0;
        texCoords.width = 49;
        texCoords.height = 114;
        worldCoords[0].left += tileSize*2.f/3.f;
        worldCoords[0].width += tileSize/3.f;
        worldCoords[0].height += tileSize;

    }
    else if(d==south) {
        worldX = x*tileSize + tileSize/3.f;
        worldY = y*tileSize + tileSize/3.f;
        texCoords.left = 75;
        texCoords.top = 0;
        texCoords.width = 49;
        texCoords.height = 114;
        worldCoords[0].width += tileSize/3.f;
        worldCoords[0].height += tileSize;
    }
    else if (d==southeast) {
        worldX = x * tileSize+tileSize/3.f;
        worldY = y*tileSize+tileSize/3.f;
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
        worldX = x * tileSize;
        worldY = y * tileSize;
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
        worldX = x * tileSize;
        worldY = y * tileSize;
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
        worldX = x*tileSize+tileSize/3.f;
        worldY = y*tileSize-tileSize/3.f;
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

activeEntity::activeEntity(activeEntType d, int x, int y, float tileSize) : Entity() {
    worldCoords = std::vector<sf::IntRect>();
    worldCoords.push_back(sf::IntRect(x*tileSize+tileSize/2.f,y*tileSize-tileSize/2.f,0,0));
    if(d == player){
        worldX = x*tileSize;
        worldY = y*tileSize;
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
