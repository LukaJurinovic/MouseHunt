#ifndef OBJECT2D_H
#define OBJECT2D_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>

class Object2D : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Object2D(QGraphicsItem* parent = nullptr);

    virtual void destroy();
    virtual void move() = 0;  // znaci da podklasa mora nadjacat metodu
    virtual void handleScreenBorder();
};

#endif // OBJECT2D_H
