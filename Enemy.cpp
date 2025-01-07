#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include "Game.h"
#include "ScreenConfig.h"
#include "Enemy.h"

extern Game* game;

Enemy::Enemy(QGraphicsItem *parent, int max_health) : Entity(parent, max_health), type(1) {

    int random_number = rand() % screenWidth;
    setPos(random_number,0);

    setPixmap(QPixmap(":/images/mis.png"));

    QTimer * timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Enemy::move);
    timer->start(50);
}

void Enemy::handleScreenBorder(){
    if (pos().y() > screenHeight){
        game->player->change_health(-1);
        game->player->check_game_over();
        game->update_health();
        destroy();
    }
}

void Enemy::move(){
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
    setPos(x(),y()+10);

    handleScreenBorder();
}
