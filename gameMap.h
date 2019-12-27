//
// Created by Tom on 12/25/19.
//

#ifndef GAME_GAMEMAP_H
#define GAME_GAMEMAP_H
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include <fstream>
#include <iostream>
#include <string>
class gameMap {


    struct mapTile {
        //depends on your sprites, good luck figuring this out lmao
        const int cellSize = 19;

        bool hasNorthWall;
        bool hasSouthWall;
        bool hasEastWall;
        bool hasWestWall;
        int worldX;
        int worldY;
        /*mapTile(bool n, bool s, bool e, bool w, int x, int y){
            hasNorthWall = n;
            hasSouthWall = s;
            hasEastWall = e;
            hasWestWall = w;
            worldX = x;
            worldY = y;
        }*/
        mapTile()= default;

    };

    mapTile** tilez;


public:
    /*reads in a map file consisting of a rectangle of ones, twos, and zeroes
     * 0 = empty tile
     * 1 = wall
     * 2 = free space
     *
     * */
    gameMap(std::string filename);
    //~gameMap();
};

void generateMap();

void getTile(int x, int y);

void renderMap(sf::RenderWindow* window);




#endif //GAME_GAMEMAP_H
