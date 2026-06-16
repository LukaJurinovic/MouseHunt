#ifndef HORIZONTALENEMYR_H
#define HORIZONTALENEMYR_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include "Enemy.h"

class HorizontalEnemyR : public Enemy {
    Q_OBJECT
public:
    HorizontalEnemyR(QGraphicsItem* parent = nullptr, int max_health = 1, int type = 1);

    void move() override;
    void handleScreenBorder() override;
};

#endif
