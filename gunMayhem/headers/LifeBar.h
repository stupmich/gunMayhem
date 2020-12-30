//
// Created by Maťo Prošovský on 30. 12. 2020.
//

#ifndef GUNMAYHEM_LIFEBAR_H
#define GUNMAYHEM_LIFEBAR_H


#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class LifeBar {
private:
    RectangleShape lifeBar;

public:
    LifeBar();
    virtual ~LifeBar();
    void initLifeBar(float x,float y);
    RectangleShape &getRect();
    float getLifeBarPositionX();
    float getLifeBarPositionY();
    void setSizeOfLifeBar(int hp);
    void setLifeBarPosition(float x, float y);

    const RectangleShape &getLifeBar() const;

    void setHealthBar(const RectangleShape &bullet);
};

#endif //GUNMAYHEM_LIFEBAR_H
