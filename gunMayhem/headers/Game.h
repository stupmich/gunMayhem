#ifndef GUNMAYHEM_GAME_H
#define GUNMAYHEM_GAME_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Platform.h"
#include "HealthBar.h"

#include "LifeBar.h"

using namespace sf;

class Game{
private:
    std::vector<Bullet*> bulletsGame;
    RenderWindow* gameWindow;
    Event event;
    VideoMode videoMode;
    Player player1;
    Player player2;
    HealthBar healthBar1;
    HealthBar healthBar2;
    LifeBar lifeBar1[3];
    LifeBar lifeBar2[3];
    int time = 0;
    Platform platforms[4];

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
    void hitboxes(std::vector<Bullet*> bullets, Player *player);
    void gameplay(Player *player, HealthBar *healthBar);
};

#endif //GUNMAYHEM_GAME_H