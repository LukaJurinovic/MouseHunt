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
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for(int i = 0, n = colliding_items.size(); i < n; ++i) {
        if(typeid(*(colliding_items[i])) == typeid(Player)) {
            game->player->takeDamage(-1);
            game->player->check_game_over();
            game->update_health();
            destroy();
            return;
        }
    }
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
    if (qAbs(game->player->x() - x()) <= 50) { // Adjust range as needed
        Projectile* projectile = new Magic();
        if (projectile && !(isDestroyed())) {
            projectile->setPos(x() + 50, y()); // Position the projectile slightly to the right of the enemy
            scene()->addItem(projectile);
            projectile->playProjectileSound(); // Play sound if implemented
        }
    }
}
