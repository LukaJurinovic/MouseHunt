#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include "Game.h"
#include "ScreenConfig.h"
#include "HorizontalEnemyR.h"

extern Game* game;

HorizontalEnemyR::HorizontalEnemyR(QGraphicsItem *parent, int max_health) : Entity(parent, max_health), type(1){

    int random_number = rand() % (screenHeight*5/6);
    setPos(screenWidth, random_number);

    setPixmap(QPixmap(":/images/enemy.png"));

    QTimer * timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &HorizontalEnemyR::move);
    timer->start(50);
}

void HorizontalEnemyR::handleScreenBorder(){
    if (pos().x() < 0){
       /* game->player->change_health(-1);
        game->player->check_game_over();
        game->update_health();*/
        destroy();
    }
}

void HorizontalEnemyR::move(){
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
    setPos(x()-10, y());

    handleScreenBorder();
}
