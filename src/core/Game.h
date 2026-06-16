#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QPushButton>
#include <QString>
#include <QPointF>
#include "Player.h"

class QGraphicsScene;
class Hud;
class EnemySpawner;

class Game : public QGraphicsView {
public:
    QGraphicsScene* scene;
    Player* player;
    Game(QWidget* parent = nullptr);

    void update_health();
    void update_score();
    void update_weapon();
    void update_weapon_image(const QString& path, const QPointF& offset);

private:
    Hud* hud;
    EnemySpawner* spawner;
    QPushButton* exitButton;
};

#endif
