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
    if (this->player.isJumping1()) {
        this->player.setVelY(-10.f);
    } else {
        this->player.setVelY(10.f);
    }
    if (this->player.getRect().getPosition().y >= 400) {
        this->player.setIsOnGround(true);
        this->player.getRect().setPosition(this->player.getRect().getPosition().x, 400);
    }
    if (this->player.getRect().getPosition().y <= 250)
    {
        this->player.setIsJumping(false);
    }
}
