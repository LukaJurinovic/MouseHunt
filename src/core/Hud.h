#ifndef HUD_H
#define HUD_H

#include <QString>
#include <QPointF>

class QGraphicsScene;
class QGraphicsRectItem;
class QGraphicsTextItem;
class QGraphicsPixmapItem;
class Player;

class Hud {
public:
    Hud(QGraphicsScene* scene, Player* player, int screenWidth);

    void updateHealth();
    void updateScore();
    void updateWeapon();
    void updateWeaponImage(const QString& path, const QPointF& offset);

private:
    Player* m_player;
    QGraphicsRectItem* container;
    QGraphicsTextItem* healthText;
    QGraphicsTextItem* scoreText;
    QGraphicsTextItem* weaponText;
    QGraphicsPixmapItem* weaponImage;
};

#endif
