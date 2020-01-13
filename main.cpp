#include <iostream>
#include <cstdlib>
#include "Game.h"

#include <SFML/Graphics.hpp>
#include "gameMap.h"


/*
 *
 * TILE CLASS
 * hasNorthWall
 * hasSouthWall
 * hasWestWall
 * hasEastWall
 * create up to four wall sprites plus a tile sprite for each cell
 *
 */

/*sf::Vector2f WorldToScreen(sf::Vector2f v)
{
    return {2.0f*v.x - 2.0f*v.y, v.x + v.y};
}
sf::Vector2f adjustVec(float x, float y, sf::Vector2f z){
    z.x+=x;
    z.y+=y;
    return z;
}
*/

int main()
{

    // create the window
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "My window");
    window.setFramerateLimit(60);
    sf::Texture spriteSheet;
    spriteSheet.loadFromFile("sprites.png");
    gameMap map("map.txt", spriteSheet);
    map.loadEntVerticies();

    sf::Texture epicTexture;
    epicTexture.loadFromFile("walls.png", sf::IntRect(0,0,49,114));
    sf::Texture epicTexture2;
    epicTexture2.loadFromFile("walls.png", sf::IntRect(49,0,49,114));

    /*
    sf::Sprite test;
    sf::Sprite test2;
    test.setTexture(floorTexture);
    test2.setTexture(floorTexture);
    test.setPosition(WorldToScreen(sf::Vector2f(0,0)));
    test2.setPosition(WorldToScreen(sf::Vector2f(19,0)));


    sf::Sprite wallTest;
    wallTest.setTexture(eastWallTexture);
    wallTest.setPosition(WorldToScreen(sf::Vector2f(19.0/3.0, -19.0/3.0)));
    wallTest.move(sf::Vector2f(0,-90));
*/
    //north wall needs an adjustment of y:-90
    //west wall needs to go y:-90 and then world space x:19/3 and y:19/3
    //east needs y:-90 and world x:19/3 y:-19/3
    //south needs y:-90 and world x:2*19/3
    /*
    sf::Sprite wall2;
    wall2.setTexture(coolTexture);
    sf::Sprite wall3;
    wall3.setTexture(coolTexture);
    sf::Sprite wall4;
    wall4.setTexture(coolTexture);
    sf::Sprite wall5;
    wall5.setTexture(coolTexture);
    sf::Sprite wall6;
    wall6.setTexture(coolTexture);
    sf::Sprite wall7;
    wall7.setTexture(coolTexture);
    sf::Sprite actualWall1;
    sf::Sprite actualWall2;
    actualWall1.setTexture(epicTexture);
    actualWall2.setTexture(epicTexture);
    wall1.setPosition(WorldToScreen(sf::Vector2f(19*5,19)));
    wall2.setPosition(WorldToScreen(sf::Vector2f(19*5,19*2)));
    wall3.setPosition(WorldToScreen(sf::Vector2f(19*4,19*2)));
    //actualWall1.setPosition(WorldToScreen(sf::Vector2f(19*3,0)));
    actualWall1.setPosition(WorldToScreen(sf::Vector2f(19*5,19*2+6)));
    actualWall1.move(sf::Vector2f(0,-77));

    actualWall2.setPosition(WorldToScreen(sf::Vector2f(19*4, 19*2+6)));
    actualWall2.move(sf::Vector2f(0,-77));
    wall4.setPosition(WorldToScreen(sf::Vector2f(19*3,19)));
    wall5.setPosition(WorldToScreen(sf::Vector2f(19*4,0)));
    wall6.setPosition(WorldToScreen(sf::Vector2f(19*5,0)));
    wall7.setPosition(WorldToScreen(sf::Vector2f(19*6,0)));
    */
    sf::VertexArray shit = sf::VertexArray(sf::Quads, 8);
   /* shit[0].position = sf::Vector2f(0.f, 0.f);
    shit[1].position = sf::Vector2f(74.f, 0.f);
    shit[2].position = sf::Vector2f(74.f, 37.f);
    shit[3].position = sf::Vector2f(0.f, 37.f);
    shit[0].texCoords = sf::Vector2f(0.f, 0.f);
    shit[1].texCoords = sf::Vector2f(74.f, 0.f);
    shit[2].texCoords = sf::Vector2f(74.f, 37.f);
    shit[3].texCoords = sf::Vector2f(0.f, 37.f);
*/
    sf::Vector2f tile1Root = WorldToScreen(sf::Vector2f(0.f, 0.f));
    sf::Vector2f tile2Root = WorldToScreen(sf::Vector2f(19, 0.f));

    sf::Vector2f jef = sf::Vector2f(0,0);


    /*
    shit[0].position = adjustVec(0,0,tile1Root);
    shit[1].position = adjustVec(75,0,tile1Root);
    shit[2].position = adjustVec(75,39,tile1Root);
    shit[3].position = adjustVec(0,39,tile1Root);
    shit[0].texCoords = sf::Vector2f(0.f, 0.f);
    shit[1].texCoords = sf::Vector2f(75.f, 0.f);
    shit[2].texCoords = sf::Vector2f(75.f, 39.f);
    shit[3].texCoords = sf::Vector2f(0.f, 39.f);
    shit[4].position = adjustVec(0,0,tile2Root);
    shit[5].position = adjustVec(75,0,tile2Root);
    shit[6].position = adjustVec(75,39,tile2Root);
    shit[7].position = adjustVec(0,39,tile2Root);
    shit[4].texCoords = sf::Vector2f(0.f, 0.f);
    shit[5].texCoords = sf::Vector2f(75.f, 0.f);
    shit[6].texCoords = sf::Vector2f(75.f, 39.f);
    shit[7].texCoords = sf::Vector2f(0.f, 39.f);

    map.addElementToVertexArray(shit, sf::Vector2f(19*3, 19*3), coolTexture);
    map.addElementToVertexArray(shit, sf::Vector2f(19*4, 19*4), coolTexture);
    map.addElementToVertexArray(shit, sf::Vector2f(19*5, 19*5), coolTexture);
    map.addElementToVertexArray(shit, sf::Vector2f(19*6, 19*6), coolTexture);
    */
/*    sf::Vector2f secondTile = WorldToScreen(sf::Vector2f(19,19));
    shit[4].position = WorldToScreen(sf::Vector2f(19,19));
    shit[5].position = WorldToScreen(sf::Vector2f(19+18,19));
    shit[6].position = WorldToScreen(sf::Vector2f(19+18,19+18));
    shit[7].position = WorldToScreen(sf::Vector2f(19,19+18));

    shit[4].texCoords = sf::Vector2f(0.f, 0.f);
    shit[5].texCoords = sf::Vector2f(74.f, 0.f);
    shit[6].texCoords = sf::Vector2f(74.f, 37.f);
    shit[7].texCoords = sf::Vector2f(0.f, 37.f);
    */

    // run the program as long as the window is open

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with yellow color
        window.clear(sf::Color::Yellow);

        // draw everything here...
        // window.draw(...);
        map.renderMap(&window);
        //window.draw(test);
        //window.draw(test2);
        //window.draw(wallTest);
        //window.draw(wall2);
        //window.draw(wall3);
        //window.draw(wall4);
        //window.draw(wall5);
        //window.draw(wall6);
        //window.draw(wall7);
        //window.draw(actualWall2);

        //window.draw(actualWall1);

        //window.draw(shit, &floorTexture);
        // end the current frame
        window.display();


    }
    return 0;
}