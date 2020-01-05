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
    private:
    struct mapTile {
        bool isEmpty;
        bool hasNorthWall;
        bool hasSouthWall;
        bool hasEastWall;
        bool hasWestWall;
        mapTile()= default;
    };
    const int cellSize = 19;

    mapTile* mapTiles;
    int cols; //x size of world
    int rows; //y size of world

    //tilez is a 2d grid stored as a 1d array for speed, use this function to get a certain index
    size_t index( int x, int y ) const { return x + cols*y; }

    sf::VertexArray floorVerticies;
    sf::VertexArray westWallVerticies;
    sf::VertexArray southWallVerticies;
    sf::VertexArray eastWallVerticies;
    sf::VertexArray northWallVerticies;

    static void emptyTile(mapTile &m){
        m.isEmpty = true;
        m.hasWestWall = false;
        m.hasEastWall = false;
        m.hasSouthWall = false;
        m.hasNorthWall = false;
    }


    /*reads in a map file consisting of a rectangle of ones, twos, and zeroes
     * 0 = empty tile
     * 1 = wall
     * 2 = free space
     *
     * */
    public:
    gameMap(std::string filename);
    //~gameMap();
    void generateMap();
    void getTile(int x, int y);
    void renderMap(sf::RenderWindow* window);

};





#endif //GAME_GAMEMAP_H
