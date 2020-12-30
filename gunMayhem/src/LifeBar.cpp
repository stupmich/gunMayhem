//
// Created by Maťo Prošovský on 30. 12. 2020.
//
#include <LifeBar.h>

LifeBar::LifeBar() {
    this->initLifeBar(0,0);
}

LifeBar::~LifeBar() {
    if (this->lifeBar.getPosition().x > 1000 || this->lifeBar.getPosition().x < -200){
        delete(this);
    }
}

RectangleShape &LifeBar::getRect()  {
    return lifeBar;
}

void LifeBar::initLifeBar(float x,float y) {
    lifeBar.setSize(Vector2f(30.f,30.f));
    lifeBar.setFillColor(Color::Red);
    lifeBar.setPosition(x, y);

}

const RectangleShape &LifeBar::getLifeBar() const {
    return lifeBar;
}

void LifeBar::setSizeOfLifeBar(int hp) {
    float f = (float) hp;
    if (hp <= 0) {
        f = 0.f;
    }
    lifeBar.setSize(Vector2f(f,20.f));
}




float LifeBar::getLifeBarPositionX() {
    return this->lifeBar.getPosition().x;
}

float LifeBar::getLifeBarPositionY() {
    return this->lifeBar.getPosition().y;
}

void LifeBar::setLifeBarPosition(float x, float y) {
    this->lifeBar.setPosition(x,y);
}
