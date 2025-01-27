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

#include <thread>
#include <mutex>
#include <condition_variable>

using namespace sf;

class Game{
private:
    std::vector<Bullet*> bulletsGame;
    RenderWindow* gameWindow;
public:
    RenderWindow *getGameWindow() const;

private:
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
    int  magSize;
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    bool ready = false;
    bool ready2 = false;
    sf::TcpSocket socket;
    char connectionType;


private:

    void initVariables();
    void initWindow();
public:

    Game();
    virtual ~Game();
    void restart();
    const bool getWindowIsOpen();
    void update();
    void pollEvents();
    void render();
    void gravitation();
    void bulletRemove(std::vector<Bullet*> bullets);
    void hitboxes(std::vector<Bullet*> bullets, Player *player);
    void gameplay(Player *player, HealthBar *healthBar);
};

#endif //GUNMAYHEM_GAME_H