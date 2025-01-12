#include <QTimer>
#include "CasterMouseEnemy.h"
#include "Game.h"
#include "ScreenConfig.h"
#include "Projectile.h"
#include "Weapons.h"

extern Game* game;

CasterMouseEnemy::CasterMouseEnemy(QGraphicsItem *parent, int max_health, int type) : Enemy(parent, max_health, type) {
    int random_numberX = abs(rand() % screenWidth - boundingRect().width());
    int random_numberY = abs(rand() % 300 + 150);
    setPos(random_numberX, random_numberY);

    setPixmap(QPixmap(":/images/pixel_mis.png"));

    QTimer * timer1 = new QTimer(this);
    connect(timer1, &QTimer::timeout, this, &CasterMouseEnemy::move);
    timer1->start(50);

    QTimer * timer2 = new QTimer(this);
    connect(timer2, &QTimer::timeout, this, &CasterMouseEnemy::fireProjectile);
    timer2->start(2000);
}

void CasterMouseEnemy::move() {
    qreal player_x = game->player->x();
    qreal enemy_x = x();
    qreal step_size = 5;

    if (player_x < enemy_x) {
        enemy_x -= step_size;
    } else if (player_x > enemy_x) {
        enemy_x += step_size;
    }

    setPos(enemy_x, y());
}

void CasterMouseEnemy::fireProjectile() {
    if(!this) return;
    if (qAbs(game->player->x() - x()) <= 50) {
        if (!scene()) return;

        Projectile* projectile = new Magic();
        if (projectile) {
            projectile->setPos(x() + 50, y());
            scene()->addItem(projectile);
            projectile->playProjectileSound();
        }
    }
}
