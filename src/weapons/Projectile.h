#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Object2D.h"

class QTimer;
class SoundEffect;
class Enemy;

class Projectile : public Object2D {
    Q_OBJECT
protected:
    int damage;
    int type;
    QTimer* timer = nullptr;
    SoundEffect* weaponSound = nullptr;

    virtual bool handleCollision(QGraphicsItem* item);
    virtual void onHitEnemy(Enemy* enemy);
    virtual int stepY() const { return -20; }
    void killOrDamage(Enemy* enemy);

public:
    Projectile(QGraphicsItem* parent = nullptr, int damage = 1, int type = 0);

    int getDamage() const;
    int getType() const;
    void playProjectileSound();
    virtual void handleScreenBorder();
    void move() override;
};

#endif
