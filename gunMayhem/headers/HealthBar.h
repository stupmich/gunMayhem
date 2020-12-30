//
// Created by Maťo Prošovský on 29. 12. 2020.
//

#ifndef GUNMAYHEM_HEALTHBAR_H
#define GUNMAYHEM_HEALTHBAR_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class HealthBar {
private:
    RectangleShape healthBar;

public:
    HealthBar();
    virtual ~HealthBar();
    void initHealthBar(float x,float y);
    RectangleShape &getRect();
    float getHealthBarPositionX();
    float getHealthBarPositionY();
    void setSizeOfHB(int hp);
    void setHealthBarPosition(float x, float y);

    const RectangleShape &getHealthBar() const;

    void setHealthBar(const RectangleShape &bullet);
};


#endif //GUNMAYHEM_HEALTHBAR_H
