#ifndef WEAPONS_H
#define WEAPONS_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "Projectile.h"

class Bullet : public Projectile {
public:
    Bullet(QGraphicsItem* parent = nullptr, int damage = -1, int type = 1);
};

class Cheese : public Projectile {
public:
    Cheese(QGraphicsItem* parent = nullptr, int damage = -1, int type = 2);
    void move() override;
};

class MouseTrap : public Projectile {
public:
    MouseTrap(QGraphicsItem* parent = nullptr, int damage = -1, int type = 3);
};

class Magic : public Projectile {
public:
    Magic(QGraphicsItem* parent = nullptr, int damage = -1, int type = 0);
    void handleScreenBorder() override;
    void move() override;
};

#endif // WEAPONS_H
