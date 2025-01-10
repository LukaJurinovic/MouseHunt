#include <Qtimer>
#include "ScreenConfig.h"
#include "FatMouseEnemy.h"
#include "Game.h"

extern Game* game;

FatMouseEnemy::FatMouseEnemy(QGraphicsItem *parent, int max_health, int type) : Enemy(parent, max_health, type) {
    setPixmap(QPixmap(":/images/fattie_mis.png"));
    int random_number = abs(rand() % screenWidth - boundingRect().width());
    setPos(random_number,0);
    sleeping = false;
    QTimer * timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Enemy::move);
    timer->start(2000);
}

void FatMouseEnemy::move() {
    if(!sleeping) {
        QList<QGraphicsItem*> colliding_items = collidingItems();
        for(int i = 0, n = colliding_items.size(); i < n; ++i) {
            if(typeid(*(colliding_items[i])) == typeid(Player)) {
                game->player->change_health(-1);
                game->player->check_game_over();
                game->update_health();
                destroy();
                return;
            }
        }
        setPos(x(), y() + 10);

        handleScreenBorder();
    }
}
