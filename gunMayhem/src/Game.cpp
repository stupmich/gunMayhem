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

    sf::Vector2f prevPosition, p2Position;
    sf::Packet packet;

    prevPosition = player1.getRect().getPosition();
    this->player1.move();
    this->player2.move();

    if (prevPosition != player1.getRect().getPosition()) {
        packet << player1.getRect().getPosition().x <<  player1.getRect().getPosition().y;
        this->socket.send(packet);
    }

    this->socket.receive(packet);

    if (packet >> p2Position.x >> p2Position.y ) {
        this->player2.getRect().setPosition(p2Position);
    }


    for (auto &bullet : this->player1.getWeapon().getBullets()) // access by reference to avoid copying
    {
        bullet->move();
    }
}

void Game::render() {
    this->gameWindow->clear();

    this->gameWindow->draw(this->player1.getRect());
    this->gameWindow->draw(this->player2.getRect());

    for (auto &bullet : this->player1.getWeapon().getBullets()) // access by reference to avoid copying
    {
        this->gameWindow->draw(bullet->getBullet());
    }
    this->gameWindow->display();
}

void Game::initVariables() {
    this->gameWindow = nullptr;


    std::cout << " (s) for server, (c) for client" << std::endl;
    std::cin >> this->connectionType;

    if (this->connectionType == 's') {
        sf::TcpListener listener;
        listener.listen(2010);
        listener.accept(this->socket);
    } else {
        socket.connect(this->ip,2010);
    }


    this->player1.initPlayer(Color::Blue);
    this->player2.initPlayer(Color::Green);
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
    while (this->gameWindow->pollEvent(this->event)) {
        switch (this->event.type) {
            case Event::Closed:
                this->gameWindow->close();
                break;
            case Event::KeyReleased:
                if (event.key.code == Keyboard::A) {
                    this->player1.setVelX(0.f);
                } else if (event.key.code == Keyboard::D) {
                    this->player1.setVelX(0.f);
                } else if (event.key.code == Keyboard::C) {
                    this->player1.shoot();
                }
                break;
        }

        if (Keyboard::isKeyPressed(Keyboard::W)) {
            if (this->player1.getIsOnGround() && !this->player1.isJumping1()) {
                this->player1.setIsOnGround(false);
                this->player1.setIsJumping(true);
            }
        } else if (Keyboard::isKeyPressed(Keyboard::A)) {
            this->player1.setVelX(-10.f);
        } else if (Keyboard::isKeyPressed(Keyboard::D)) {
            this->player1.setVelX(10.f);
        }
    }
}

void Game::gravitation() {
    if (this->player1.isJumping1()) {
        this->player1.setVelY(-10.f);
    } else {
        this->player1.setVelY(10.f);
    }
    if (this->player1.getRect().getPosition().y >= 400) {
        this->player1.setIsOnGround(true);
        this->player1.getRect().setPosition(this->player1.getRect().getPosition().x, 400);
    }
    if (this->player1.getRect().getPosition().y <= 250)
    {
        this->player1.setIsJumping(false);
    }
}
