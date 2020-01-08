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
        std::vector<Entity> entities;
        mapTile()= default;
    };


    /*This is the dimension of one square in world space.
     * Passing multiples of this value to WorldToScreen
     * allows you to make tiles tesselate. This value
     * is approximately equal to the height of a floor
     * sprite divided by two or the width of a floor sprite
     * divided by four. */
    const float tileSize = 19.f;

    mapTile* mapTiles;

    int cols; //x size of world in number of tiles
    int rows; //y size of world in number of tiles

    //tilez is a 2d grid stored as a 1d array for speed, use this function to get a certain index
    size_t index( int x, int y ) const { return x + cols*y; }

    sf::VertexArray floorVerticies;
    sf::VertexArray otherVerticies;
    sf::Texture spriteSheet;



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
    void addElementToVertexArray(sf::VertexArray &v, sf::Vector2f worldCoords, sf::Texture, float zHeight);

    gameMap(std::string filename, sf::Texture textures[5]);
    //~gameMap();
    void generateMap();
    void getTile(int x, int y);
    void renderMap(sf::RenderWindow* window);
    void loadVerticies();


};


static sf::Vector2f WorldToScreen(sf::Vector2f v)
{
    return {2.0f*v.x - 2.0f*v.y, v.x + v.y};
}
static sf::Vector2f adjustVec(float x, float y, sf::Vector2f v){
    v.x+=x;
    v.y+=y;
    return v;
}



#endif //GAME_GAMEMAP_H
