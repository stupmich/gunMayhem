#include "Game.h"
#include <chrono>

Game::Game() {
    this->initVariables();
    this->initWindow();
}

Game::~Game() {
    delete this->gameWindow;
}

void Game::update() {

    this->pollEvents();

    sf::Packet packet7;

    if (this->player1.isRestart()) {
        packet7 << 1;
    } else {
        packet7 << 0;
    }
    this->socket.send(packet7);
    this->socket.receive(packet7);
    int restart = 0;
    if (packet7 >> restart) {
        if (restart == 1) {
            this->player2.setRestart(true);
        }
    }

    if (this->player2.isRestart() && this->player1.isRestart()) {
        this->restart();
        this->player1.setRestart(false);
        this->player2.setRestart(false);
    }

    if(this->player1.getLife() > 0 && this->player2.getLife() > 0) {

        this->gravitation();

        sf::Vector2f prevPosition, p2Position;
        int prevHP1, hp1, prevHP2, hp2, prevLife1, prevLife2, life1, life2;
        //pohyb***************************************************************************
        sf::Packet packet;

        prevPosition = player1.getRect().getPosition();
        this->player1.move();
        this->player2.move();

        if (prevPosition != player1.getRect().getPosition()) {
            packet << player1.getRect().getPosition().x << player1.getRect().getPosition().y;
            this->socket.send(packet);
        }

        this->socket.receive(packet);

        if (packet >> p2Position.x >> p2Position.y) {
            if (this->player2.getRect().getPosition().x < p2Position.x) {
                this->player2.setLookingRight(true);
            } else {
                this->player2.setLookingRight(false);
            }
            this->player2.getRect().setPosition(p2Position);
        }
        //pohyb***************************************************************************

        //hpcka****************************************************************
        sf::Packet packet4;

        prevHP1 = player1.getHP();
        prevHP2 = player2.getHP();
        this->hitboxes(this->player1.getWeapon().getBullets(), &this->player2);
        this->hitboxes(this->player2.getWeapon().getBullets(), &this->player1);

        if (prevHP1 != player1.getHP()) {
            packet4 << player1.getHP();

        }
        this->socket.send(packet4);
        this->socket.receive(packet4);

        if (packet4 >> hp1) {
            this->player2.setHP(hp1);
        }

        if (prevHP2 != player2.getHP()) {
            packet4 << player2.getHP();

        }
        this->socket.send(packet4);
        this->socket.receive(packet4);

        if (packet4 >> hp2) {
            this->player1.setHP(hp2);
        }

        this->healthBar1.setSizeOfHB(this->player1.getHP());
        this->healthBar2.setSizeOfHB(this->player2.getHP());
        //hpcka****************************************************************

        //zivoty**********************************************************************
        sf::Packet packet5;
        prevLife1 = this->player1.getLife();
        prevLife2 = this->player2.getLife();

        this->gameplay(&this->player1, &this->healthBar1);
        this->gameplay(&this->player2, &this->healthBar2);

        if (prevLife1 != player1.getLife()) {
            packet5 << player1.getLife();

        }
        this->socket.send(packet5);
        this->socket.receive(packet5);

        if (packet5 >> life1) {
            this->player2.setLife(life1);
        }

        if (prevLife2 != player2.getLife()) {
            packet5 << player2.getLife();

        }
        this->socket.send(packet5);
        this->socket.receive(packet5);

        if (packet5 >> life2) {
            this->player1.setLife(life2);
        }

        //zivoty**********************************************************************

        //pocet guliek***********************************************************

        sf::Packet packet6;

        int magSize2;
        int ij = 0;
        for (auto &bullet: this->player1.getWeapon().getBullets()) {
            ij++;
        }

        if (ij != this->magSize) {
            packet6 << ij - this->magSize;
            this->magSize = ij;
        } else {
            packet6 << 0;
        }

        this->socket.send(packet6);
        this->socket.receive(packet6);

        if (packet6 >> magSize2) {
            for (int i = 0; i < magSize2; i++) {
                this->player2.shoot();
            }
        }
        magSize2 = 0;

        //gulky***************************************************************************
        sf::Packet packet2;
        sf::Packet packet3;

        float *aX = new float[500];
        float *aY = new float[500];

        for (int i = 0; i < 500; ++i) {
            aX[i] = 0;
            aY[i] = 0;
        }

        for (auto &bullet : this->player1.getWeapon().getBullets()) {
            bullet->move();
            packet2 << bullet->getBulletPositionX();
            packet3 << bullet->getBulletPositionY();
        }

        this->socket.send(packet2);
        this->socket.receive(packet2);
        this->socket.send(packet3);
        this->socket.receive(packet3);

        for (int i = 0; i < this->player2.getWeapon().getBullets().size(); i++) {
            if (packet2 >> aX[i] && packet3 >> aY[i]) {

            }
        }

        int i = 0;
        for (auto &bullet : this->player2.getWeapon().getBullets()) {
            bullet->setBulletPosition(aX[i], aY[i]);
            i++;

        }

        packet2.clear();
        packet3.clear();

        delete[] aX;
        delete[] aY;
        //gulky***************************************************************************
        this->bulletRemove(this->player2.getWeapon().getBullets());
        this->bulletRemove(this->player1.getWeapon().getBullets());

        this->healthBar1.setSizeOfHB(this->player1.getHP());
        this->healthBar2.setSizeOfHB(this->player2.getHP());



    }
}

void Game::render() {


    if (this->player1.getLife() <= 0 || this->player2.getLife() <= 0) {
        this->gameWindow->clear();
        if(this->player1.getLife() <= 0) {
            sf::Image victory;
            victory.loadFromFile("Images/defeat.png");
            sf::Texture texture;
            texture.loadFromImage(victory);
            sf::Sprite sprite;
            sprite.setTexture(texture, true);
            this->gameWindow->draw(sprite);
        } else if (this->player2.getLife() <= 0) {
            sf::Image victory;
            victory.loadFromFile("Images/Victory.jpg");
            sf::Texture texture;
            texture.loadFromImage(victory);
            sf::Sprite sprite;
            sprite.setTexture(texture, true);
            this->gameWindow->draw(sprite);
        }
        this->gameWindow->display();

    } else {
        this->gameWindow->clear();
        for (int i = 0; i < 4;i++) {
            this->gameWindow->draw(this->platforms[i].getRect());
        }

        if(this->player1.getLife() > 0) {
            this->gameWindow->draw(this->player1.getRect());
        }
        if(this->player2.getLife() > 0) {
            this->gameWindow->draw(this->player2.getRect());
        }
        for (auto &bullet : this->player1.getWeapon().getBullets()) // access by reference to avoid copying
        {
            this->gameWindow->draw(bullet->getBullet());
        }

        for (auto &bullet : this->player2.getWeapon().getBullets()) // access by reference to avoid copying
        {
            this->gameWindow->draw(bullet->getBullet());
        }

        for (int i = 0; i < this->player1.getLife(); i++) {
            this->gameWindow->draw(this->lifeBar1[i].getLifeBar());
        }

        for (int i = 0; i < this->player2.getLife(); i++) {
            this->gameWindow->draw(this->lifeBar2[i].getLifeBar());
        }

        if(this->player1.getLife() > 0) {
            this->gameWindow->draw(this->healthBar1.getHealthBar());
        }
        if(this->player2.getLife() > 0) {
            this->gameWindow->draw(this->healthBar2.getHealthBar());
        }

        this->gameWindow->display();
    }
}

void Game::initVariables() {
    this->gameWindow = nullptr;
    this->magSize = 0;
    std::cout << " *******CONTROL*******" << std::endl;
    std::cout << "   Movement - W A S D" << std::endl;
    std::cout << "       Shoot - C" << std::endl;
    std::cout << "  Vote for restart - R" << std::endl;
    std::cout << " *********************" << std::endl;
    std::cout << " (s) for server, (c) for client" << std::endl;
    std::cin >> this->connectionType;

    if (this->connectionType == 's') {
        sf::TcpListener listener;
        listener.listen(2010);
        listener.accept(this->socket);
    } else {
        sf::IpAddress sIP;
        std::cout << "Enter server IP." << std::endl;
        std::cin >> sIP;
        if(!socket.connect(sIP,2010)) {
            std::cout << "You have been connected to the server." << std::endl;
        } else {
            std::cout << "Connection failed." << std::endl;
        }
    }

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

    LifeBar l11;
    LifeBar l12;
    LifeBar l13;

    LifeBar l21;
    LifeBar l22;
    LifeBar l23;

    l11.initLifeBar(20,15);
    l12.initLifeBar(60,15);
    l13.initLifeBar(100,15);

    l21.initLifeBar(690,15);
    l22.initLifeBar(730,15);
    l23.initLifeBar(770,15);


    this->lifeBar1[0] = l11;
    this->lifeBar1[1] = l12;
    this->lifeBar1[2] = l13;

    this->lifeBar2[0] = l21;
    this->lifeBar2[1] = l22;
    this->lifeBar2[2] = l23;

    this->healthBar1.initHealthBar(20,60);
    this->healthBar2.initHealthBar(700,60);
    this->player1.initPlayer(Color::Red);
    this->player2.initPlayer(Color::Green);
    this->ready = true;

}

void Game::initWindow() {
    sf::Context context;
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    this->gameWindow = new RenderWindow(this->videoMode, "GunMayhem", sf::Style::Titlebar | sf::Style::Close);
    this->gameWindow->setFramerateLimit(60);
    this->gameWindow->setVerticalSyncEnabled(true);

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
            case Event::KeyPressed:
                if (event.key.code == Keyboard::Escape) {
                    this->gameWindow->close();
                } else if(event.key.code == Keyboard::A) {
                    this->player1.setVelX(-10.f);
                } else if(event.key.code == Keyboard::D) {
                    this->player1.setVelX(10.f);
                }
                break;

            case Event::KeyReleased:
                if(event.key.code == Keyboard::A) {
                    this->player1.setVelX(0.f);
                } else if(event.key.code == Keyboard::D) {
                    this->player1.setVelX(0.f);
                } else if(event.key.code == Keyboard::C) {
                    this->player1.shoot();
                } else if(event.key.code == Keyboard::R) {
                    this->player1.setRestart(true);
                }
                break;

        }
        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            if (this->player1.getIsOnGround() && !this->player1.isJumping1())
            {
                this->player1.setIsOnGround(false);
                this->player1.setIsJumping(true);
            }

        }
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            if (this->player1.getIsOnGround() && !this->player1.isJumping1())
            {
                this->player1.setIsOnGround(false);
                this->player1.getRect().setPosition(this->player1.getRect().getPosition().x,this->player1.getRect().getPosition().y + 61);
            }

        }
    }
}


void Game::hitboxes(std::vector<Bullet*> bullets, Player *player) {
    for (auto &bullet : bullets) {
        if(player->getRect().getGlobalBounds().intersects(bullet->getRect().getGlobalBounds())) {
            player->setHP((player->getHP() - 25));
            bullet->setBulletPosition(2000,2000);
        }
    }

}


void Game::gameplay(Player *player, HealthBar *healthBar) {
    if(player->getHP() <= 0 || player->getRect().getPosition().y > 1200) {
        player->getRect().setPosition(400,-200);
        player->setLife(player->getLife() - 1);
        player->setHP(100);
        healthBar->setSizeOfHB(100);
    }
}


void Game::gravitation() {
    if(this->player1.isJumping1()) {
        this->player1.setVelY(-10.f);
        time++;
        if (time == 15) {
            time = 0;
            this->player1.setIsJumping(false);
        }
    }else {
        this->player1.setVelY(10.f);
    }
    for (int i = 0; i < 4;i++) {
        if ((this->platforms[i].getRect().getGlobalBounds().intersects(this->player1.getRect().getGlobalBounds())) ) {

            this->player1.setIsOnGround(true);
            if (!this->player1.isJumping1() && this->player1.getIsOnGround())
                this->player1.getRect().setPosition(this->player1.getRect().getPosition().x,this->platforms[i].getRect().getPosition().y - 50);

            break;
        } else {
            this->player1.setIsOnGround(false);
        }

    }
}

void Game::bulletRemove(std::vector<Bullet*> bullets) {
    if(!bullets.empty()) {
        for(unsigned int i = 0; i < bullets.size() ; i ++) {
            if (abs(bullets[i]->getBulletPositionX() > 1200)) {
                bullets.erase(bullets.begin() + (i++));
            }
        }
    }
}

RenderWindow *Game::getGameWindow() const {
    return gameWindow;
}

void Game::restart() {
    this->player1.setLife(3);
    this->player1.setHP(100);
    this->player2.setLife(3);
    this->player2.setHP(100);
    this->player1.getRect().setPosition(100,-20);
    this->player1.getRect().setPosition(100,-20);
}



