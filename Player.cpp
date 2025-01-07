#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include "Weapons.h"
#include "ScreenConfig.h"
#include "Player.h"

Player::Player(QGraphicsItem *parent, int max_health) : Entity(parent, max_health), Score(), weapon(1){

    setPixmap(QPixmap(":/images/player.png"));

    actionTimer = new QTimer(this);
    connect(actionTimer, &QTimer::timeout, this, &Player::processActions);
    actionTimer->start(50);

    canShoot = true;
    shootCooldownTimer = new QTimer(this);
    shootCooldownTimer->setSingleShot(true);
    connect(shootCooldownTimer, &QTimer::timeout, this, [this]() {
        canShoot = true;
    });

    canMove = true; // Player can move initially
    moveCooldownTimer = new QTimer(this);
    moveCooldownTimer->setSingleShot(true);
    connect(moveCooldownTimer, &QTimer::timeout, this, [this]() {
        canMove = true;
    });
}

int Player::getWeapon() {
    return weapon;
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
    if(!canMove)
        return;

    int newX = x() + delta_x;
    int newY = y() + delta_y;
    if (newX < 0)
        newX = 0;
    else if (newX + 100 > screenWidth)
        newX = screenWidth - 100;

    if (newY < 0)
        newY = 0;
    else if (newY + 100 > screenHeight)
        newY = screenHeight - 100;
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
            move(40,0);
            break;
        case Qt::Key_Right:
            move(40,0);
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
            break;
        case Qt::Key_2:
            weapon = 2;
            break;
        case Qt::Key_3:
            weapon = 3;
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

void Player::handleScreenBorder() {/*a eto hahah*/}
