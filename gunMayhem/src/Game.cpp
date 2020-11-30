//
// Created by micha on 27. 11. 2020.
//

#include "Game.h"

Game::Game() {
    this->initVariables();
    this->initWindow();
}

Game::~Game() {
    this->gameWindow = nullptr;
}

void Game::update() {
    this->pollEvents();
    this->gravitation();
    this->player.move();
    for (auto &bullet : this->player.getWeapon().getBullets()) // access by reference to avoid copying
    {
        bullet->move();
    }
}

void Game::render() {
    this->gameWindow->clear();



    for (int i = 0; i < 4;i++) {
        this->gameWindow->draw(this->platforms[i].getRect());
    }
    this->gameWindow->draw(this->player.getRect());
    
    for (auto &bullet : this->player.getWeapon().getBullets()) // access by reference to avoid copying
    {
        this->gameWindow->draw(bullet->getBullet());
    }
    this->gameWindow->display();
}

void Game::initVariables() {
    this->gameWindow = nullptr;
    this->player.initPlayer();
    Platform p1;
    Platform p2;
    Platform p3;
    Platform p4;
    p1.initPlatform(250,20,50,120);
    p2.initPlatform(250,20,500,120);
    p3.initPlatform(450,20,150,250);
    p4.initPlatform(700,20,50,400);
    this->platforms[0] = p1;
    this->platforms[1] = p2;
    this->platforms[2] = p3;
    this->platforms[3] = p4;

}

void Game::initWindow() {
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->gameWindow = new RenderWindow(this->videoMode, "GunMayhem", sf::Style::Titlebar | sf::Style::Close);
    this->gameWindow->setFramerateLimit(60);
}

const bool Game::getWindowIsOpen() {
    return this->gameWindow->isOpen();
}

void Game::pollEvents() {
    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        if (this->player.getIsOnGround() && !this->player.isJumping1())
        {
            this->player.setIsOnGround(false);
            this->player.setIsJumping(true);
        }

    }
    if (Keyboard::isKeyPressed(Keyboard::S))
    {
        if (this->player.getIsOnGround() && !this->player.isJumping1())
        {
            this->player.setIsOnGround(false);
            this->player.getRect().setPosition(this->player.getRect().getPosition().x,this->player.getRect().getPosition().y + 10);
        }

    }

    while (this->gameWindow->pollEvent(this->event)) {
        switch (this->event.type) {
            case Event::Closed:
                this->gameWindow->close();
                break;
            case Event::KeyPressed:
                if (event.key.code == Keyboard::Escape) {
                    this->gameWindow->close();
                } else if(event.key.code == Keyboard::A) {
                    this->player.setVelX(-10.f);
                } else if(event.key.code == Keyboard::D) {
                    this->player.setVelX(10.f);
                }
                break;

            case Event::KeyReleased:
                if(event.key.code == Keyboard::A) {
                    this->player.setVelX(0.f);
                } else if(event.key.code == Keyboard::D) {
                    this->player.setVelX(0.f);
                } else if(event.key.code == Keyboard::C) {
                    this->player.shoot();
                }
                break;
        }
    }
}

void Game::gravitation() {
    if(this->player.isJumping1()) {
        this->player.setVelY(-10.f);
        time++;
        if (time == 15) {
            time = 0;
            this->player.setIsJumping(false);
        }
    }else {
        this->player.setVelY(10.f);
    }
    for (int i = 0; i < 4;i++) {
        if (this->platforms[i].getRect().getGlobalBounds().intersects(this->player.getRect().getGlobalBounds()) &&
        this->platforms[i].getRect().getPosition().y >= this->player.getRect().getPosition().y + 40) {
            this->player.setIsOnGround(true);
            if (!this->player.isJumping1())
                this->player.setVelY(0);
            break;
        } else {
            this->player.setIsOnGround(false);
        }

    }
}
