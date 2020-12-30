//
// Created by Maťo Prošovský on 29. 12. 2020.
//

#include <HealthBar.h>

HealthBar::HealthBar() {
    this->initHealthBar(0,0);
}

HealthBar::~HealthBar() {
    if (this->healthBar.getPosition().x > 1000 || this->healthBar.getPosition().x < -200){
        delete(this);
    }
}

RectangleShape &HealthBar::getRect()  {
    return healthBar;
}

void HealthBar::initHealthBar(float x,float y) {
    healthBar.setSize(Vector2f(100.f,20.f));
    healthBar.setFillColor(Color::Green);
    healthBar.setPosition(x, y);

}

const RectangleShape &HealthBar::getHealthBar() const {
    return healthBar;
}

void HealthBar::setSizeOfHB(int hp) {
    float f = (float) hp;
    if (hp <= 0) {
        f = 0.f;
    }
    healthBar.setSize(Vector2f(f,20.f));
}

void HealthBar::setHealthBar(const RectangleShape &healthBar) {
    HealthBar::healthBar = healthBar;
}



float HealthBar::getHealthBarPositionX() {
    return this->healthBar.getPosition().x;
}

float HealthBar::getHealthBarPositionY() {
    return this->healthBar.getPosition().y;
}

void HealthBar::setHealthBarPosition(float x, float y) {
    this->healthBar.setPosition(x,y);
}