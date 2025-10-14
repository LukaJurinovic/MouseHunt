#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include "Weapons.h"
#include "Projectile.h"
#include "ScreenConfig.h"
#include "Game.h"
#include "Enemy.h"
#include "Player.h"

extern Game* game;

Player::Player(QGraphicsItem *parent, int max_health) : Entity(parent, max_health), Score(), weapon(1), weaponName("Gun") {
    setPixmap(QPixmap(":/images/evil_cat_with_gun.png"));
    actionTimer = new QTimer(this);
    connect(actionTimer, &QTimer::timeout, this, &Player::processActions);
    actionTimer->start(50);

    canShoot = true;
    canMove = true;
    iFrames=false;

    damageSoundPlayer=new QMediaPlayer(this);
    damageSoundPlayer->setSource(QUrl("qrc:/sounds/meow.wav"));
    audioOutput = new QAudioOutput(this);
    audioOutput->setVolume(1);

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
        projectile = new Cheese();
        break;
    case 3:
        projectile = new MouseTrap();
        break;
    default:
        projectile = new Bullet();
    }

    if (projectile) {
        if(projectile->getType() == 1) {
            projectile->setPos(x() + 180, y());
        }
        else {
           projectile->setPos(x() + 42, y());
        }
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

    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (QGraphicsItem* item : colliding_items) {
        Enemy* enemy = dynamic_cast<Enemy*>(item);
        if (enemy) {
            enemy->Object2D::destroy();
            takeDamage(-1);
            game->update_health();
        }
    }

    canMove = false;
    moveCooldownTimer->start(50);
}

void Player::check_game_over() {
    if(getHealth() <= 0) {
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
            weaponName = "Gun";
            setPixmap(QPixmap(":/images/evil_cat_with_gun.png"));
            game->update_weapon();
            game->update_weapon_image(":/images/desert_eagle.png", weapon);
            break;
        case Qt::Key_2:
            weapon = 2;
            weaponName = "Cheese";
            setPixmap(QPixmap(":/images/evil_cat.png"));
            game->update_weapon();
            game->update_weapon_image(":/images/cheese.png", weapon);
            break;
        case Qt::Key_3:
            weapon = 3;
            weaponName = "Mouse Trap";
            setPixmap(QPixmap(":/images/evil_cat.png"));
            game->update_weapon();
            game->update_weapon_image(":/images/mouse_trap.png", weapon);
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

void Player::takeDamage(int damage) {
    if(!iFrames){
        Health::change_health(damage);
        damageSoundPlayer->setAudioOutput(audioOutput);
        if (damageSoundPlayer->playbackState() == QMediaPlayer::PlayingState) {
            damageSoundPlayer->setPosition(0);
        } else if (damageSoundPlayer->playbackState() == QMediaPlayer::StoppedState) {
            damageSoundPlayer->play();
        }
        check_game_over();

        iFrames = true;
        QTimer::singleShot(1000, this, [this]() {
            if (this->scene()) { // za izbjec seg fault nakon sta macka umre
                iFrames = false;
            }
        });
    }

}
