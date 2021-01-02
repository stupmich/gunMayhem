#include <Weapon.h>

void Weapon::shoot(bool right,float x,float y) {
    Bullet* b;
    b = new Bullet(right,x,y);
    this->bullets.push_back(b);
}

const std::vector<Bullet *> &Weapon::getBullets() const {
    return this->bullets;

}

void Weapon::add(Bullet * bull) {
    this->bullets.push_back(bull);
}

Weapon::~Weapon() {
    for (auto &bullet : this->bullets) {
        delete bullet;
    }
}




