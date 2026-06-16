#include "Enemy.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QRandomGenerator>
#include "SoundEffect.h"
#include "Game.h"
#include "ScreenConfig.h"

extern Game* game;

Enemy::Enemy(QGraphicsItem *parent, int max_health, int type)
    : Entity(parent, max_health), type(type), sleepTimer(nullptr), sleeping(false) {
    setPixmap(QPixmap(":/images/mouse.png"));

    int maxX = qMax(1, static_cast<int>(screenWidth - boundingRect().width()));
    setPos(QRandomGenerator::global()->bounded(maxX), 0);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Enemy::move);
    timer->start(50);
}

void Enemy::handleScreenBorder() {
    if (pos().y() > screenHeight) {
        game->player->takeDamage(1);
        game->update_health();
        Object2D::destroy();
    }
}

int Enemy::getType() const {
    return type;
}

void Enemy::sleep(int duration) {
    if (sleeping)
        return;
    sleeping = true;
    sleepTimer = new QTimer(this);
    sleepTimer->setSingleShot(true);
    connect(sleepTimer, &QTimer::timeout, this, [this]() {
        sleeping = false;
        sleepTimer->deleteLater();
        sleepTimer = nullptr;
    });
    sleepTimer->start(duration);
}

void Enemy::destroy() {
    SoundEffect::playOnce("qrc:/sounds/squeak.ogg");
    Object2D::destroy();
}

void Enemy::move() {
    setPos(x(), y() + 10);
    handleScreenBorder();
}

void Enemy::fireProjectile() {}
