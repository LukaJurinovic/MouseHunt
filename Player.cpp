#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include "Weapons.h"
#include "Projectile.h"
#include "ScreenConfig.h"
#include "Game.h"
#include "Player.h"

extern Game* game;

Player::Player(QGraphicsItem *parent, int max_health) : Entity(parent, max_health), Score(), weapon(1), weaponName("Bullet") {
    setPixmap(QPixmap(":/images/player.png"));
    actionTimer = new QTimer(this);
    connect(actionTimer, &QTimer::timeout, this, &Player::processActions);
    actionTimer->start(50);

    canShoot = true;
    canMove = true;

    shootCooldownTimer = new QTimer(this);
    shootCooldownTimer->setSingleShot(true);
    connect(shootCooldownTimer, &QTimer::timeout, this, [this]() {
        canShoot = true;
    });

    moveCooldownTimer = new QTimer(this);
    moveCooldownTimer->setSingleShot(true);
    connect(moveCooldownTimer, &QTimer::timeout, this, [this]() {
        canMove = true;
    });
}

int Player::getWeapon() {
    return weapon;
}

QString Player::getWeaponName() {
    return weaponName;
}

void Player::fire_projectile() {
    if (!canShoot) return;

    Projectile* projectile = nullptr;
    switch (weapon) {
    case 1:
        projectile = new Bullet();
        break;
    case 2:
        projectile = new Fireball();
        break;
    case 3:
        projectile = new IceShard();
        break;
    default:
        projectile = new Bullet();
    }

    if (projectile) {
        projectile->setPos(x() + 42, y());
        scene()->addItem(projectile);
        projectile->playProjectileSound();
    }

    canShoot = false;
    shootCooldownTimer->start(500);
}

void Player::destroy() {}

void Player::move(int delta_x, int delta_y) {
    if (!canMove)
        return;

    int newX = x() + delta_x;
    int newY = y() + delta_y;

    handleScreenBorder(newX, newY);

    setPos(newX, newY);

    canMove = false;
    moveCooldownTimer->start(50);
}

void Player::check_game_over() {
    if(getHealth() == 0) {
        QCoreApplication::quit();
    }
}

void Player::keyPressEvent(QKeyEvent *event) {
    activeKeys.insert(event->key());
    switch (event->key()) {
        case Qt::Key_Left:
            move(200,0);
            break;
        case Qt::Key_Right:
            move(200,0);
            break;
        case Qt::Key_Up:
            move(0, -20);
            break;
        case Qt::Key_Down:
            move(0, 20);
            break;
        case Qt::Key_Space:
            fire_projectile();
            break;
        case Qt::Key_1:
            weapon = 1;
            weaponName = "Bullet";
            game->update_weapon();
            break;
        case Qt::Key_2:
            weapon = 2;
            weaponName = "Fireball";
            game->update_weapon();
            break;
        case Qt::Key_3:
            weapon = 3;
            weaponName = "Ice Shard";
            game->update_weapon();
            break;
    }
}

void Player::keyReleaseEvent(QKeyEvent *event) {
    activeKeys.remove(event->key());
}

void Player::processActions() {
    int delta_x = 0;
    int delta_y = 0;

    if (activeKeys.contains(Qt::Key_Left)) delta_x -= 40;
    if (activeKeys.contains(Qt::Key_Right)) delta_x += 40;
    if (activeKeys.contains(Qt::Key_Up)) delta_y -= 20;
    if (activeKeys.contains(Qt::Key_Down)) delta_y += 20;

    // normalizacija za dijagonale
    float length = std::sqrt(delta_x * delta_x + delta_y * delta_y);
    if (length > 0) {
        delta_x = static_cast<int>(std::round(delta_x / length * 20));
        delta_y = static_cast<int>(std::round(delta_y / length * 20));
    }

    move(delta_x, delta_y);
}

void Player::handleScreenBorder(int& newX, int& newY) {
    if (newX < 0)
        newX = 0;
    else if (newX + boundingRect().width() > screenWidth)
        newX = screenWidth - boundingRect().width();

    if (newY < 70)
        newY = 70;
    else if (newY + boundingRect().height() > screenHeight)
        newY = screenHeight - boundingRect().height();
}
