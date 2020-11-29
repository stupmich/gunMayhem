//
// Created by micha on 28. 11. 2020.
//

#include <Weapon.h>

void Weapon::shoot(bool right,float x,float y) {
    Bullet* b;
    b = new Bullet(right,x,y);
    this->bullets.push_back(b);
}

const std::vector<Bullet *> &Weapon::getBullets() const {
    return bullets;
}



