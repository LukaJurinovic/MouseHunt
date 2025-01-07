#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include "Entity.h"

class Enemy : public Entity {
    Q_OBJECT
public:
    Enemy(QGraphicsItem* parent = nullptr, int max_health = 1);

    void move() override;
    void handleScreenBorder() override;
    int type;
};

#endif // ENEMY_H
