//
// Created by micha on 27. 11. 2020.
//

#include "Player.h"

void Player::initPlayer(Color c) {
    this->rect.setSize(Vector2f(30.f,50.f));
    this->rect.setPosition(100.f,-300.f);
    this->rect.setFillColor(c);
    this->lookingRight = true;
}

RectangleShape &Player::getRect()  {
    return rect;
}

void Player::setVelY(float velY) {
    Player::velY = velY;
}

void Player::setVelX(float velX) {
    Player::velX = velX;
}

void Player::move() {
    this->rect.move(this->velX,this->velY);
    if (this->velX > 0) {
        this->lookingRight = true;
    } else if (this->velX < 0){
        this->lookingRight = false;
    }
}

bool Player::isJumping1()  {
    return isJumping;
}

bool Player::getIsOnGround()  {
    return isOnGround;
}

void Player::setIsJumping(bool isJumping) {
    Player::isJumping = isJumping;
}

void Player::setIsOnGround(bool isOnGround) {
    Player::isOnGround = isOnGround;
}


void Player::shoot() {
    if (this->lookingRight) {
        weapon.shoot(this->lookingRight,this->rect.getPosition().x + this->rect.getGlobalBounds().width, this->rect.getPosition().y);
    } else {
        weapon.shoot(this->lookingRight,this->rect.getPosition().x , this->rect.getPosition().y);
    }
}


Player::Player() {

}

Player::~Player() {

}

const Weapon &Player::getWeapon() const {
    return weapon;
}


