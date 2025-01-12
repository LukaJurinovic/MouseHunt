#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QSet>
#include <QMediaPlayer>
#include "Entity.h"
#include "Score.h"

class Player : public Entity, public Score {
    Q_OBJECT

private:
    QTimer* actionTimer;
    QTimer* shootCooldownTimer;
    QTimer* moveCooldownTimer;
    QSet<int> activeKeys;
    QMediaPlayer* damageSoundPlayer;
    QAudioOutput* audioOutput;

    int weapon;
    QString weaponName;
    bool canShoot;
    bool canMove;
    bool iFrames;
    void processActions();
public:
    Player(QGraphicsItem* parent = nullptr, int max_health = 0);

    int getWeapon();
    QString getWeaponName();
    void fire_projectile() override;
    void handleScreenBorder(int& newX, int& newY);
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void move(int delta_x, int delta_y);
    void takeDamage(int damage);
    void check_game_over();
    void destroy() override;
};

#endif // PLAYER_H
