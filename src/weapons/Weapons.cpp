#include "Weapons.h"

#include "SoundEffect.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include "ScreenConfig.h"

extern Game* game;

Bullet::Bullet(QGraphicsItem* parent, int damage, int type) : Projectile(parent, damage, type) {
    setPixmap(QPixmap(":/images/bullet.png"));
    weaponSound = new SoundEffect("qrc:/sounds/bullet.wav", this);
}

Cheese::Cheese(QGraphicsItem* parent, int damage, int type) : Projectile(parent, damage, type) {
    setPixmap(QPixmap(":/images/cheese.png"));
}

void Cheese::onHitEnemy(Enemy* enemy) {
    if (enemy->getType() != getType())
        return;
    enemy->sleep(1000);
    killOrDamage(enemy);
}

MouseTrap::MouseTrap(QGraphicsItem* parent, int damage, int type) : Projectile(parent, damage, type) {
    setPixmap(QPixmap(":/images/mouse_trap.png"));
    weaponSound = new SoundEffect("qrc:/sounds/mouse_trap.wav", this);
}

void MouseTrap::onHitEnemy(Enemy* enemy) {
    playProjectileSound();
    if (enemy->getType() != getType())
        return;
    enemy->sleep(1000);
    killOrDamage(enemy);
}

Magic::Magic(QGraphicsItem* parent, int damage, int type) : Projectile(parent, damage, type) {
    setPixmap(QPixmap(":/images/purple.png"));
    weaponSound = new SoundEffect("qrc:/sounds/caster_purple.wav", this);
}

void Magic::handleScreenBorder() {
    if (pos().y() > screenHeight)
        destroy();
}

int Magic::stepY() const {
    return 50;
}

bool Magic::handleCollision(QGraphicsItem* item) {
    if (dynamic_cast<Player*>(item)) {
        game->player->takeDamage(getDamage());
        game->update_health();
        return true;
    }
    return false;
}
