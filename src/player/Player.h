#ifndef PLAYER_H
#define PLAYER_H

#include <QSet>
#include <memory>
#include <vector>
#include "Entity.h"
#include "Score.h"

class QTimer;
class QKeyEvent;
class Weapon;
class SoundEffect;

class Player : public Entity, public Score {
    Q_OBJECT

private:
    QTimer* actionTimer;
    QTimer* shootCooldownTimer;
    QTimer* moveCooldownTimer;
    QSet<int> activeKeys;
    SoundEffect* damageSound;

    std::vector<std::unique_ptr<Weapon>> weapons;
    int currentIndex;

    bool canShoot;
    bool canMove;
    bool iFrames;
    void processActions();

public:
    Player(QGraphicsItem* parent = nullptr, int max_health = 0);
    ~Player() override;

    Weapon* currentWeapon() const;
    QString getWeaponName() const;
    void selectWeapon(int index);

    void fire_projectile() override;
    void handleScreenBorder(int& newX, int& newY);
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void move(int delta_x, int delta_y);
    void takeDamage(int amount);
    void check_game_over();
    void destroy() override;
};

#endif
