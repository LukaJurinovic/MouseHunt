#ifndef HORIZONTALENEMYL_H
#define HORIZONTALENEMYL_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include "Enemy.h"

class HorizontalEnemyL : public Enemy {
    Q_OBJECT
public:
    HorizontalEnemyL(QGraphicsItem* parent = nullptr, int max_health = 1, int type = 2);

    void move() override;
    void handleScreenBorder() override;
};

#endif // HORIZONTALENEMYL_H
