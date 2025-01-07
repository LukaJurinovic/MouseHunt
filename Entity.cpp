#include "Entity.h"

Entity::Entity(QGraphicsItem *parent, int max_health) : Object2D(parent), Health(max_health) {}

void Entity::move() {}

void Entity::fire_projectile() {}
