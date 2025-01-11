#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include "Game.h"
#include "Weapons.h"
#include "Player.h"
#include "ScreenConfig.h"
#include "Enemy.h"

extern Game* game;

Bullet::Bullet(QGraphicsItem* parent, int damage, int type) : Projectile(parent, damage, type) {
    setPixmap(QPixmap(":/images/bullet.png"));
    weaponSound = new QMediaPlayer();
    weaponSound->setSource(QUrl("qrc:/sounds/bullet.wav"));
}

Cheese::Cheese(QGraphicsItem* parent, int damage, int type) : Projectile(parent, damage, type) {
    setPixmap(QPixmap(":/images/cheese.png"));
    weaponSound = new QMediaPlayer();
    //weaponSound->setSource(QUrl("qrc:/sounds/bullet.wav"));
}

void Cheese::move() {
    handleScreenBorder();
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (QGraphicsItem* item : colliding_items) {
        if (Enemy* enemy = dynamic_cast<Enemy*>(item)) {
            if (enemy->getType() == getType()) {
                enemy->change_health(getDamage());
                enemy->sleep(1000);
                if (enemy->getHealth() <= 0) {
                    enemy->sleeping = false;
                    enemy->destroy();
                    game->player->increase(1);
                    game->update_score();
                }
            }
            destroy();
            return;
        }
    }
    setPos(x(), y() - 20);
}

MouseTrap::MouseTrap(QGraphicsItem* parent, int damage, int type) : Projectile(parent, damage, type) {
    setPixmap(QPixmap(":/images/mouse_trap.png"));
    weaponSound = new QMediaPlayer();
    //weaponSound->setSource(QUrl("qrc:/sounds/bullet.wav"));
}

Magic::Magic(QGraphicsItem *parent, int damage, int type)  : Projectile(parent, damage, type) {
    setPixmap(QPixmap(":/images/purple.png"));
    weaponSound = new QMediaPlayer();
    weaponSound->setSource(QUrl("qrc:/sounds/bullet.wav"));
}

void Magic::handleScreenBorder() {
    if (pos().y() > screenHeight) {
        destroy();
        return;
    }
}

void Magic::move() {
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
