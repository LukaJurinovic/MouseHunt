#include "Object2D.h"

#include <QTimer>

Object2D::Object2D(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {}

void Object2D::destroy() {
    const QList<QTimer*> timers = findChildren<QTimer*>();
    for (QTimer* timer : timers)
        timer->stop();

    if (scene())
        scene()->removeItem(this);
    deleteLater();
}

void Object2D::handleScreenBorder() {}
