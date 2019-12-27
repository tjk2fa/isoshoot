//
// Created by Tom on 12/23/19.
//


#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class Game{
private:
    sf::RenderWindow* window;
    sf::Event ev;
    //sf::VideoMode vm;
public:
    Game();
    virtual ~Game();
    void update();
    void render();
    const bool running() const;

};