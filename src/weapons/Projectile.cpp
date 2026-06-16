#include "Projectile.h"

#include <QList>
#include <QTimer>
#include <QGraphicsScene>
#include "SoundEffect.h"
#include "Enemy.h"
#include "Game.h"

extern Game* game;

Projectile::Projectile(QGraphicsItem* parent, int damage, int type)
    : Object2D(parent), damage(damage), type(type) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Projectile::move);
    timer->start(50);
}

int Projectile::getDamage() const {
    return damage;
}

int Projectile::getType() const {
    return type;
}

void Projectile::playProjectileSound() {
    if (weaponSound)
        weaponSound->play();
}

void Projectile::handleScreenBorder() {
    if (pos().y() < 0)
        destroy();
}

void Projectile::killOrDamage(Enemy* enemy) {
    enemy->damage(getDamage());
    if (enemy->isDead()) {
        enemy->destroy();
        game->player->increase(1);
        game->update_score();
    }
}

void Projectile::onHitEnemy(Enemy* enemy) {
    if (enemy->getType() != getType())
        return;
    killOrDamage(enemy);
}

bool Projectile::handleCollision(QGraphicsItem* item) {
    Enemy* enemy = dynamic_cast<Enemy*>(item);
    if (!enemy)
        return false;
    onHitEnemy(enemy);
    return true;
}

void Projectile::move() {
    handleScreenBorder();
    if (!scene())
        return;

    const QList<QGraphicsItem*> colliding_items = collidingItems();
    for (QGraphicsItem* item : colliding_items) {
        if (handleCollision(item)) {
            destroy();
            return;
        }
    }
    setPos(x(), y() + stepY());
}
