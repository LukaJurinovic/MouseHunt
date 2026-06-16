#include <QTimer>
#include <QRandomGenerator>
#include "CasterMouseEnemy.h"
#include "Game.h"
#include "ScreenConfig.h"
#include "Projectile.h"
#include "Weapons.h"

extern Game* game;

CasterMouseEnemy::CasterMouseEnemy(QGraphicsItem *parent, int max_health, int type) : Enemy(parent, max_health, type) {
    int maxX = qMax(1, static_cast<int>(screenWidth - boundingRect().width()));
    setPos(QRandomGenerator::global()->bounded(maxX),
           QRandomGenerator::global()->bounded(150, 450));

    setPixmap(QPixmap(":/images/caster_mouse.png"));

    QTimer* moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &CasterMouseEnemy::move);
    moveTimer->start(50);

    QTimer* fireTimer = new QTimer(this);
    connect(fireTimer, &QTimer::timeout, this, &CasterMouseEnemy::fireProjectile);
    fireTimer->start(2000);
}

void CasterMouseEnemy::move() {
    qreal player_x = game->player->x();
    qreal enemy_x = x();
    const qreal step_size = 5;

    if (player_x < enemy_x)
        enemy_x -= step_size;
    else if (player_x > enemy_x)
        enemy_x += step_size;

    setPos(enemy_x, y());
}

void CasterMouseEnemy::fireProjectile() {
    if (!scene())
        return;
    if (qAbs(game->player->x() - x()) > 50)
        return;

    Projectile* projectile = new Magic();
    projectile->setPos(x() + 50, y());
    scene()->addItem(projectile);
    projectile->playProjectileSound();
}
