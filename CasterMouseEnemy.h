#ifndef CASTERMOUSEENEMY_H
#define CASTERMOUSEENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include "Enemy.h"

class CasterMouseEnemy : public Enemy {
    Q_OBJECT
public:
    CasterMouseEnemy(QGraphicsItem* parent = nullptr, int max_health = 1, int type = 3);
    void move() override;
    void fireProjectile() override;
};

#endif // CASTERMOUSEENEMY_H
