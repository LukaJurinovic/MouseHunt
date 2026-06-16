#ifndef WEAPONS_H
#define WEAPONS_H

#include "Projectile.h"

class Enemy;

class Bullet : public Projectile {
public:
    Bullet(QGraphicsItem* parent = nullptr, int damage = 1, int type = 1);
};

class Cheese : public Projectile {
public:
    Cheese(QGraphicsItem* parent = nullptr, int damage = 1, int type = 2);
protected:
    void onHitEnemy(Enemy* enemy) override;
};

class MouseTrap : public Projectile {
public:
    MouseTrap(QGraphicsItem* parent = nullptr, int damage = 1, int type = 3);
protected:
    void onHitEnemy(Enemy* enemy) override;
};

class Magic : public Projectile {
public:
    Magic(QGraphicsItem* parent = nullptr, int damage = 1, int type = 0);
    void handleScreenBorder() override;
protected:
    bool handleCollision(QGraphicsItem* item) override;
    int stepY() const override;
};

#endif
