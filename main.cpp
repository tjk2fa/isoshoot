#include <iostream>
#include <cstdlib>
#include "Game.h"

#include <SFML/Graphics.hpp>
#include "gameMap.h"

int main()
{

    // create the window
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "My window");
    window.setFramerateLimit(60);
    sf::Texture spriteSheet;
    spriteSheet.loadFromFile("sprites.png");
    gameMap map("map.txt", spriteSheet);
    map.loadEntVerticies();

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

        // clear the window
        window.clear(sf::Color::Black);

        //draw everything to the screen in the correct order
        sf::CircleShape circle = sf::CircleShape(1, 50);
        sf::CircleShape circle2 = sf::CircleShape(1, 50);
        sf::CircleShape circle3 = sf::CircleShape(1, 50);
        sf::CircleShape circle4 = sf::CircleShape(1, 50);

        circle.setPosition(WorldToScreen(sf::Vector2f(+9,-9)));
        circle2.setPosition(WorldToScreen(sf::Vector2f(+9+6,-9+18)));
        circle3.setPosition(WorldToScreen(sf::Vector2f(+9+6,-9+18)));
        circle4.setPosition(WorldToScreen(sf::Vector2f(+9+6,-9+18)));

        //circle.move(WorldToScreen(sf::Vector2f(18,18)));
       //circle.move(sf::Vector2f(35,0));
       map.renderMap(&window);
       window.draw(circle);
       window.draw(circle4);

        // end the current frame
        window.display();


    }
    return 0;
}