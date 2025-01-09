#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include "Game.h"
#include "ScreenConfig.h"
#include "HorizontalEnemyL.h"

extern Game* game;

HorizontalEnemyL::HorizontalEnemyL(QGraphicsItem *parent, int max_health, int type) : Enemy(parent, max_health, type) {
    int random_number = rand() % (screenHeight*5/6) + 70;
    setPos(0, random_number);

    setPixmap(QPixmap(":/images/enemy.png"));

    QTimer * timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &HorizontalEnemyL::move);
    timer->start(50);
}

void HorizontalEnemyL::handleScreenBorder(){
    if (pos().x() > screenWidth){
        /*game->player->change_health(-1);
        game->player->check_game_over();
        game->update_health();*/
        destroy();
    }
}

void HorizontalEnemyL::move(){
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
    setPos(x()+10, y());

    handleScreenBorder();
}
