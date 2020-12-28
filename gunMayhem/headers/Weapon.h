//
// Created by micha on 28. 11. 2020.
//
#pragma SPARK_NO_PREPROCESSOR
#ifndef GUNMAYHEM_WEAPON_H
#define GUNMAYHEM_WEAPON_H




#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

#include "Bullet.h"

class Weapon {
private:
   std::vector<Bullet*> bullets;

public:
    void shoot(bool right,float x,float y);
    void add(Bullet* bull);
    const std::vector<Bullet *> &getBullets() const;

};
#endif //GUNMAYHEM_WEAPON_H
