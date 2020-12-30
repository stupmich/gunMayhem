#include <Bullet.h>

Bullet::Bullet(bool right,float x,float y) {
    this->initBullet(right,x,y);
}

Bullet::~Bullet() {
    if (this->bullet.getPosition().x > 1000 || this->bullet.getPosition().x < -200){
        delete(this);
    }
}

RectangleShape &Bullet::getRect()  {
    return bullet;
}

void Bullet::initBullet(bool right,float x,float y) {
    bullet.setSize(Vector2f(10.f,5.f));
    bullet.setFillColor(Color::Blue);
    if (right){
        bullet.setPosition(x, y);
        this->bulletVel = 10.f;
    } else {
        bullet.setPosition(x , y);
        this->bulletVel = -10.f;
    }

}

void Bullet::move() {
    this->bullet.move(this->bulletVel,0.f);
}

float Bullet::getBulletVel() const {
    return bulletVel;
}

void Bullet::setBulletVel(float bulletVel) {
    Bullet::bulletVel = bulletVel;
}

const RectangleShape &Bullet::getBullet() const {
    return bullet;
}

void Bullet::setBullet(const RectangleShape &bullet) {
    Bullet::bullet = bullet;
}



float Bullet::getBulletPositionX() {
    return this->bullet.getPosition().x;
}

float Bullet::getBulletPositionY() {
    return this->bullet.getPosition().y;
}

void Bullet::setBulletPosition(float x, float y) {
    this->bullet.setPosition(x,y);
}
