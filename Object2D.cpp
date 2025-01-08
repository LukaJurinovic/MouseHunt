#include "Object2D.h"

Object2D::Object2D(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {}

void Object2D::destroy() {
    scene()->removeItem(this);
    delete this;
}

void Object2D::handleScreenBorder(){}
