#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QPushButton>
#include "Player.h"

class Game: public QGraphicsView {
public:
    QGraphicsScene* scene;
    Player* player;
    QGraphicsRectItem* hudContainer;
    QGraphicsTextItem* show_health;
    QGraphicsTextItem* show_score;
    QGraphicsTextItem* show_weapon;
    QPushButton* exitButton;
    Game(QWidget* parent = 0);

    template <typename EnemyType>

    void spawn(int period);
    void update_health();
    void update_score();
    void update_weapon();
};

#endif // GAME_H
