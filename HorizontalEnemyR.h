#ifndef HORIZONTALENEMYR_H
#define HORIZONTALENEMYR_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include "Entity.h"

class HorizontalEnemyR : public Entity {
    Q_OBJECT
public:
    HorizontalEnemyR(QGraphicsItem* parent = nullptr, int max_health = 1);

    void move() override;
    void handleScreenBorder() override;
    int type;
};

#endif // HORIZONTALENEMYR_H
