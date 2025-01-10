#ifndef WEAPONS_H
#define WEAPONS_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "Projectile.h"

class Bullet : public Projectile {
public:
    Bullet(QGraphicsItem* parent = nullptr, int damage = -1, int type = 1);
};

class Fireball : public Projectile {
public:
    Fireball(QGraphicsItem* parent = nullptr, int damage = -1, int type = 2);
};

class IceShard : public Projectile {
public:
    IceShard(QGraphicsItem* parent = nullptr, int damage = -1, int type = 3);
};

class LaserBeam : public Projectile {
public:
    LaserBeam(QGraphicsItem* parent = nullptr, int damage = -1, int type = 0);
    void handleScreenBorder() override;
    void move() override;
};

#endif // WEAPONS_H
