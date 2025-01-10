#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include "Game.h"
#include "Weapons.h"
#include "Player.h"
#include "ScreenConfig.h"

extern Game* game;

Bullet::Bullet(QGraphicsItem* parent, int damage, int type) : Projectile(parent, damage, type) {
    setPixmap(QPixmap(":/images/bullet.png"));
    weaponSound = new QMediaPlayer();
    weaponSound->setSource(QUrl("qrc:/sounds/bullet.wav"));
}

Fireball::Fireball(QGraphicsItem* parent, int damage, int type) : Projectile(parent, damage, type) {
    setPixmap(QPixmap(":/images/fireball.png"));
    weaponSound = new QMediaPlayer();
    weaponSound->setSource(QUrl("qrc:/sounds/bullet.wav"));
}

IceShard::IceShard(QGraphicsItem* parent, int damage, int type) : Projectile(parent, damage, type) {
    //setPixmap(QPixmap(":/images/iceshard.png"));
    //weaponSound = new QMediaPlayer();
    //weaponSound->setSource(QUrl("qrc:/sounds/bullet.wav"));
}

LaserBeam::LaserBeam(QGraphicsItem *parent, int damage, int type)  : Projectile(parent, damage, type) {
    setPixmap(QPixmap(":/images/laser_beam.png"));
    weaponSound = new QMediaPlayer();
    weaponSound->setSource(QUrl("qrc:/sounds/bullet.wav"));
}

void LaserBeam::handleScreenBorder() {
    if (pos().y() > screenHeight) {
        destroy();
        return;
    }
}

void LaserBeam::move() {
    handleScreenBorder();
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (QGraphicsItem* item : colliding_items) {
        if (Player* player = dynamic_cast<Player*>(item)) {
            game->player->change_health(getDamage());
            game->player->check_game_over();
            game->update_health();
            destroy();
            return;
        }
    }
    setPos(x(), y() + 50);
}
