#ifndef HORIZONTALENEMYL_H
#define HORIZONTALENEMYL_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include "Entity.h"

class HorizontalEnemyL : public Entity {
    Q_OBJECT
public:
    HorizontalEnemyL(QGraphicsItem* parent = nullptr, int max_health = 1);

    void move() override;
    void handleScreenBorder() override;
    int type;
};

#endif // HORIZONTALENEMYL_H
