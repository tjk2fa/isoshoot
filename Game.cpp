//
// Created by Tom on 12/23/19.
//

#include "Game.h"
Game::Game(){
    window = new sf::RenderWindow(sf::VideoMode(640,480),"Yuh, aye", sf::Style::Titlebar | sf::Style::Close);
}

Game::~Game(){
    delete window;
}

void Game::update(){
    while(running()){
        while(window->pollEvent(ev)) {
            switch(ev.type){
                case sf::Event::Closed:
                    window->close();
                    break;
            }
        }
    }

}



void Game::render(){
    window->clear();
    sf::Texture coolTexture;
    coolTexture.loadFromFile("tiles.png", sf::IntRect(0,0,74,37));

    sf::Sprite wall1;
    wall1.setTexture(coolTexture);
    sf::Sprite wall2;
    wall2.setTexture(coolTexture);
    sf::Sprite wall3;
    wall2.setTexture(coolTexture);

    wall1.setPosition(0,0);
    window->draw(wall1);
    window->display(); //tells game that window is done drawing

}




const bool Game::running() const{
    return window->isOpen();
}