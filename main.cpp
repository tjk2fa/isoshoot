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

sf::Vector2f WorldToScreen(sf::Vector2f v)
{
    return {2.0f*v.x - 2.0f*v.y, v.x + v.y};
}



int main()
{
    gameMap map("map.txt");

    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    sf::Texture coolTexture;
    coolTexture.loadFromFile("tiles.png", sf::IntRect(0,0,74,37));
    sf::Texture epicTexture;
    epicTexture.loadFromFile("walls.png", sf::IntRect(0,0,49,114));
    sf::Texture epicTexture2;
    epicTexture2.loadFromFile("walls.png", sf::IntRect(49,0,49,114));
    /*
    sf::Sprite wall1;
    wall1.setTexture(coolTexture);
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
    sf::VertexArray shit = sf::VertexArray(sf::Quads, 4);
    shit[0].position = sf::Vector2f(0.f, 0.f);
    shit[1].position = sf::Vector2f(74.f, 0.f);
    shit[2].position = sf::Vector2f(74.f, 37.f);
    shit[3].position = sf::Vector2f(0.f, 37.f);
    shit[0].texCoords = sf::Vector2f(0.f, 0.f);
    shit[1].texCoords = sf::Vector2f(74.f, 0.f);
    shit[2].texCoords = sf::Vector2f(74.f, 37.f);
    shit[3].texCoords = sf::Vector2f(0.f, 37.f);


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

        // clear the window with black color
        window.clear(sf::Color::Yellow);

        // draw everything here...
        // window.draw(...);
        /*
        window.draw(wall1);
        window.draw(wall2);
        window.draw(wall3);
        //window.draw(wall4);
        //window.draw(wall5);
        //window.draw(wall6);
        //window.draw(wall7);
        window.draw(actualWall2);

        window.draw(actualWall1);
        */
        window.draw(shit, &coolTexture);
        // end the current frame
        window.display();


    }

    return 0;
}