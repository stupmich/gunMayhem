//
// Created by Maťo Prošovský on 30. 11. 2020.
//

#ifndef GUNMAYHEM_PLATFORM_H
#define GUNMAYHEM_PLATFORM_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class Platform {
private:
    RectangleShape rect;
    float Y;
    float X;


public:
    Platform();

    virtual ~Platform();

    RectangleShape &getRect();

    void initPlatform(float x, float y, float xP, float yP);

    float getX() const;
    float getY() const;

    void setX(float x);
    void setY(float y);
};




#endif //GUNMAYHEM_PLATFORM_H
