//
// Created by Maťo Prošovský on 30. 11. 2020.
//

#include "Platform.h"

void Platform::initPlatform( float x, float y, float xP, float yP) {
    this->rect.setSize(Vector2f(x,y));
    this->rect.setPosition(xP,yP);
    this->rect.setFillColor(Color::Blue);
}

RectangleShape &Platform::getRect()  {
    return rect;
}

void Platform::setY(float y) {
    Platform::Y = y;
}

void Platform::setX(float x) {
    Platform::X = x;
}

float Platform::getY() const {
    return Y;
}

float Platform::getX() const {
    return X;
}

Platform::Platform() {
    this->initPlatform( 0,0,0,0);
}

Platform::~Platform() {

}