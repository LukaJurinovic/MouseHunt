#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <stdlib.h>
#include "Game.h"
#include "ScreenConfig.h"
#include "Enemy.h"

extern Game* game;

Enemy::Enemy(QGraphicsItem *parent, int max_health, int type) : Entity(parent, max_health), type(type) {
    setPixmap(QPixmap(":/images/mis.png"));
    int random_number = abs(rand() % screenWidth - boundingRect().width());
    setPos(random_number,0);
    destroyed = false;
    QTimer * timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Enemy::move);
    timer->start(50);
}

void Enemy::handleScreenBorder(){
    if (pos().y() > screenHeight && !destroyed){
        game->player->takeDamage(-1);
        game->player->check_game_over();
        game->update_health();
        scene()->removeItem(this);
        delete this;
    }
}

int Enemy::getType() {
    return type;
}

void Enemy::sleep(int duration) {
    sleepTimer = nullptr;
    if (!sleeping) {
        sleeping = true;
        sleepTimer = new QTimer(this);
        connect(sleepTimer, &QTimer::timeout, [this]() {
            sleeping = false;
            delete sleepTimer;
            sleepTimer = nullptr;
        });

        sleepTimer->start(duration);
    }
}

void Enemy::destroy()
{
    if (destroyed) return;
    destroyed = true;

    if (scene()) {
        scene()->removeItem(this);
    }

    QMediaPlayer* mediaPlayer = new QMediaPlayer();
    QAudioOutput* audioOutput = new QAudioOutput();
    mediaPlayer->setAudioOutput(audioOutput);
    mediaPlayer->setSource(QUrl("qrc:/sounds/squeak.ogg"));
    audioOutput->setVolume(1);

    mediaPlayer->play();

    connect(mediaPlayer, &QMediaPlayer::playbackStateChanged, this, [=](QMediaPlayer::PlaybackState state) {
        if (state == QMediaPlayer::StoppedState) {
            mediaPlayer->deleteLater();
            audioOutput->deleteLater();

            QTimer::singleShot(0, this, &QObject::deleteLater);
        }
    });
}

bool Enemy::isDestroyed() const {
    return destroyed;
}

void Enemy::move(){
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for(int i = 0, n = colliding_items.size(); i < n; ++i) {
        if(typeid(*(colliding_items[i])) == typeid(Player) && !destroyed) {
            game->player->takeDamage(-1);
            game->player->check_game_over();
            game->update_health();
            scene()->removeItem(this);
            delete this;
            return;
        }
    }
    setPos(x(), y() + 10);

    handleScreenBorder();
}

void Enemy::fireProjectile() {}
