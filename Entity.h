#ifndef ENTITY_H
#define ENTITY_H

#include "Object2D.h"
#include "Health.h"

class Entity : public Object2D, public Health {
public:
    Entity(QGraphicsItem* parent = nullptr, int max_health = 0);
    void move() override;
    virtual void fire_projectile();
    virtual void handleScreenBorder() override;
};

#endif // ENTITY_H
