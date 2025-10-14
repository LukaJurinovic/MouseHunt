#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QAudioOutput>
#include <QMediaPlayer>
#include "Object2D.h"

class Projectile : public Object2D {
    Q_OBJECT
private:
    QAudioOutput* audioOutput;
protected:
    int damage;
    int type;
    QTimer* timer;
    QMediaPlayer* weaponSound;
public:
    Projectile(QGraphicsItem* parent = nullptr, int damage = 0, int type = 0);

    int getDamage() const;
    int getType() const;
    void playProjectileSound();
    virtual void handleScreenBorder();
    void destroy();
    void move();
};

#endif // PROJECTILE_H
