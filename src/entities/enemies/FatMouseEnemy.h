#ifndef FATMOUSEENEMY_H
#define FATMOUSEENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include "Enemy.h"

class FatMouseEnemy : public Enemy {
    Q_OBJECT
public:
    FatMouseEnemy(QGraphicsItem* parent = nullptr, int max_health = 3, int type = 2);
    void move() override;
};


#endif
