//
// Created by micha on 27. 11. 2020.
//

#ifndef GUNMAYHEM_PLAYER_H
#define GUNMAYHEM_PLAYER_H


#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>


#include "Weapon.h"
using namespace sf;

class Player {
private:
    RectangleShape rect;
    bool isJumping = false;
    float velY;
    float velX;
    bool lookingRight;
    bool isOnGround = true;
    Weapon weapon;


public:
    Player();

    virtual ~Player();

    RectangleShape &getRect();
    bool isJumping1();
    bool getIsOnGround();

    void setVelY(float velY);
    void setVelX(float velX);
    void setIsOnGround(bool isOnGround);
    void setIsJumping(bool isJumping);

    float getVelY() const;
    float getVelX() const;

    bool isLookingRight() const;

    const Weapon &getWeapon() const;


    void initPlayer();
    void moveRight();
    void moveLeft();
    void move();
    void jump();
    void shoot();
};



#endif //GUNMAYHEM_PLAYER_H
