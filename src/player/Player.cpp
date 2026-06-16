#include "Player.h"

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <QCoreApplication>
#include <cmath>
#include "Weapon.h"
#include "Projectile.h"
#include "SoundEffect.h"
#include "ScreenConfig.h"
#include "Game.h"
#include "Enemy.h"

extern Game* game;

Player::Player(QGraphicsItem *parent, int max_health)
    : Entity(parent, max_health), Score(), currentIndex(0),
      canShoot(true), canMove(true), iFrames(false) {
    weapons.push_back(std::make_unique<GunWeapon>());
    weapons.push_back(std::make_unique<CheeseWeapon>());
    weapons.push_back(std::make_unique<MouseTrapWeapon>());
    setPixmap(QPixmap(currentWeapon()->playerPixmap()));

    damageSound = new SoundEffect("qrc:/sounds/meow.wav", this);

    actionTimer = new QTimer(this);
    connect(actionTimer, &QTimer::timeout, this, &Player::processActions);
    actionTimer->start(50);

    shootCooldownTimer = new QTimer(this);
    shootCooldownTimer->setSingleShot(true);
    connect(shootCooldownTimer, &QTimer::timeout, this, [this]() { canShoot = true; });

    moveCooldownTimer = new QTimer(this);
    moveCooldownTimer->setSingleShot(true);
    connect(moveCooldownTimer, &QTimer::timeout, this, [this]() { canMove = true; });
}

Player::~Player() = default;

Weapon* Player::currentWeapon() const {
    return weapons[currentIndex].get();
}

QString Player::getWeaponName() const {
    return currentWeapon()->name();
}

void Player::selectWeapon(int index) {
    if (index < 0 || index >= static_cast<int>(weapons.size()))
        return;
    currentIndex = index;
    setPixmap(QPixmap(currentWeapon()->playerPixmap()));
    game->update_weapon();
    game->update_weapon_image(currentWeapon()->hudIconPath(), currentWeapon()->hudIconOffset());
}

void Player::fire_projectile() {
    if (!canShoot)
        return;

    Projectile* projectile = currentWeapon()->createProjectile();
    const QPointF muzzle = currentWeapon()->muzzleOffset();
    projectile->setPos(x() + muzzle.x(), y() + muzzle.y());
    scene()->addItem(projectile);
    projectile->playProjectileSound();

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

    const QList<QGraphicsItem*> colliding_items = collidingItems();
    for (QGraphicsItem* item : colliding_items) {
        if (Enemy* enemy = dynamic_cast<Enemy*>(item)) {
            enemy->Object2D::destroy();
            takeDamage(1);
            game->update_health();
        }
    }

    canMove = false;
    moveCooldownTimer->start(50);
}

void Player::check_game_over() {
    if (isDead())
        QCoreApplication::quit();
}

void Player::keyPressEvent(QKeyEvent *event) {
    activeKeys.insert(event->key());
    switch (event->key()) {
    case Qt::Key_Left:  move(200, 0); break;
    case Qt::Key_Right: move(200, 0); break;
    case Qt::Key_Up:    move(0, -20); break;
    case Qt::Key_Down:  move(0, 20); break;
    case Qt::Key_Space: fire_projectile(); break;
    case Qt::Key_1:     selectWeapon(0); break;
    case Qt::Key_2:     selectWeapon(1); break;
    case Qt::Key_3:     selectWeapon(2); break;
    }
}

void Player::keyReleaseEvent(QKeyEvent *event) {
    activeKeys.remove(event->key());
}

void Player::processActions() {
    int delta_x = 0;
    int delta_y = 0;

    if (activeKeys.contains(Qt::Key_Left))  delta_x -= 40;
    if (activeKeys.contains(Qt::Key_Right)) delta_x += 40;
    if (activeKeys.contains(Qt::Key_Up))    delta_y -= 20;
    if (activeKeys.contains(Qt::Key_Down))  delta_y += 20;

    float length = std::sqrt(static_cast<float>(delta_x * delta_x + delta_y * delta_y));
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

void Player::takeDamage(int amount) {
    if (iFrames)
        return;

    Health::damage(amount);
    damageSound->play();
    check_game_over();

    iFrames = true;
    QTimer::singleShot(1000, this, [this]() {
        if (scene())
            iFrames = false;
    });
}
