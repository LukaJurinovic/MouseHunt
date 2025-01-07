#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "Player.h"

class Game: public QGraphicsView {
public:
    QGraphicsScene* scene;
    Player* player;
    QGraphicsTextItem* show_health;
    QGraphicsTextItem* show_score;
    Game(QWidget* parent = 0);
    template <typename EnemyType>
    void spawn(int period);
    void update_health();
    void update_score();
};

#endif // GAME_H
