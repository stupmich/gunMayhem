#include "Player.h"

void Player::initPlayer(Color c) {
    this->rect.setSize(Vector2f(30.f,50.f));
    this->rect.setPosition(100.f,-300.f);
    this->rect.setFillColor(c);
    this->lookingRight = true;
    this->HP = 100;
    this->Life = 3;
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

bool Player::isLookingRight() const{
    return lookingRight;
}

void Player::setLookingRight(bool look) {
    lookingRight = look;
}

int Player::getHP() {
    return HP;
}

void Player::setHP(int hp) {
    Player::HP = hp;
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
        weapon.shoot(this->lookingRight,this->rect.getPosition().x + this->rect.getGlobalBounds().width, this->rect.getPosition().y + 10);
    } else {
        weapon.shoot(this->lookingRight,this->rect.getPosition().x + 1, this->rect.getPosition().y + 10);
    }
}


Player::Player() {

}

Player::~Player() {

}

const Weapon &Player::getWeapon() const {
    return weapon;
}

int Player::getLife() const {
    return Life;
}

void Player::setLife(int life) {
    Life = life;
}

void Player::setPosition(float parX, float parY) {
    std::cout << parX << parY;
    this->rect.setPosition(parX, parY);
}
