#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include "Entity.h"

class Enemy : public Entity {
    Q_OBJECT
private:
    int type;
public:
    Enemy(QGraphicsItem* parent = nullptr, int max_health = 1, int type = 1);

    void move() override;
    virtual void fireProjectile();
    void handleScreenBorder() override;
    int getType();
};

#endif // ENEMY_H
