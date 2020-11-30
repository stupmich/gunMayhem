//
// Created by micha on 27. 11. 2020.
//

#ifndef GUNMAYHEM_GAME_H
#define GUNMAYHEM_GAME_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
using namespace sf;

class Game{
private:
    RenderWindow* gameWindow;
    Event event;
    VideoMode videoMode;
    Player player1;
    Player player2;

    bool pressed;

    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    sf::TcpSocket socket;
    char connectionType;

    void initVariables();
    void initWindow();
public:
    Game();
    virtual ~Game();

    const bool getWindowIsOpen();

    void update();
    void pollEvents();
    void render();
    void gravitation();
};


#endif //GUNMAYHEM_GAME_H

