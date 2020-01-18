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
#include "Entity.h"

class gameMap {


    private:
    struct mapTile {
        std::vector<Entity> entities;
        bool empty;
        mapTile(){
            entities = std::vector<Entity>();
            empty = false;
        }
    };


    /*This is the dimension of one square in world space.
     * Passing multiples of this value to WorldToScreen
     * allows you to make tiles tesselate. This value
     * is approximately equal to the height of a floor
     * sprite divided by two or the width of a floor sprite
     * divided by four. */
    const float tileSize = 18.f;

    mapTile* mapTiles;

    int size; //world is a square of this size

    //tilez is a 2d grid stored as a 1d array for speed, use this function to get a certain index
    size_t index( int x, int y ) const { return x + size*y; }

    sf::VertexArray floorVerticies;
    sf::VertexArray verticies;
    sf::Texture spriteSheet;





    /*reads in a map file consisting of a square of characters in plaintext
     * 2 = free space
     * 0 = empty tile
     * n,s,e,w = wall in respective direction
     * i,j,k,l = corner in ne, se, sw, nw direction
     *
     * */
    public:
    void loadEntityToVertexArray(sf::VertexArray &v, Entity e);

    gameMap(std::string filename, sf::Texture sheet);
    ~gameMap();
    void generateMap();
    void getTile(int x, int y);
    void renderMap(sf::RenderWindow* window);
    void loadEntVerticies();


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
