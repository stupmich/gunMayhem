#ifndef GUNMAYHEM_BULLET_H
#define GUNMAYHEM_BULLET_H

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>


using namespace sf;

class Bullet {
private:
    float bulletVel;
    RectangleShape bullet;

public:
    Bullet(bool right,float x,float y);
    virtual ~Bullet();
    void initBullet(bool right,float x,float y);
    void move();
    RectangleShape &getRect();
    float getBulletVel() const;
    float getBulletPositionX();
    float getBulletPositionY();

    void setBulletVel(float bulletVel);
    void setBulletPosition(float x, float y);

    const RectangleShape &getBullet() const;

    void setBullet(const RectangleShape &bullet);

};
#endif //GUNMAYHEM_BULLET_H
