#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include "Game.h"
#include "Weapons.h"

extern Game* game;

Bullet::Bullet(QGraphicsItem* parent, int damage, int type) : Projectile(parent, damage, type) {
    setPixmap(QPixmap(":/images/bullet.png"));
    weaponSound = new QMediaPlayer();
    weaponSound->setSource(QUrl("qrc:/sounds/bullet.wav"));
}

Fireball::Fireball(QGraphicsItem* parent, int damage, int type) : Projectile(parent, damage, type) {
    //setPixmap(QPixmap(":/images/fireball.png"));
    //weaponSound = new QMediaPlayer();
    //bulletsound->setSource(QUrl("qrc:/sounds/bullet.wav"));
}

IceShard::IceShard(QGraphicsItem* parent, int damage, int type) : Projectile(parent, damage, type) {
    //setPixmap(QPixmap(":/images/iceshard.png"));
    //weaponSound = new QMediaPlayer();
    //bulletsound->setSource(QUrl("qrc:/sounds/bullet.wav"));
}
