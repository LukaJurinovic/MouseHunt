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
    setPixmap(QPixmap(":/images/obicni_mis.png"));
    int random_number = abs(rand() % screenWidth - boundingRect().width());
    setPos(random_number,0);
    QTimer * timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Enemy::move);
    timer->start(50);
}

void Enemy::handleScreenBorder(){
    if (pos().y() > screenHeight){
        game->player->takeDamage(-1);
        game->update_health();
        Object2D::destroy();
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

void Enemy::destroy() {
    if (scene()) {
        scene()->removeItem(this);
    }
    disconnect();
    // pristup bez flaga, manje fleksibilan, ali nama je entitet van scene efektivno mrtav pa je bolji fit
    QMediaPlayer* mediaPlayer = new QMediaPlayer();
    QAudioOutput* audioOutput = new QAudioOutput();
    audioOutput->setVolume(1);
    mediaPlayer->setAudioOutput(audioOutput);
    mediaPlayer->setSource(QUrl("qrc:/sounds/squeak.ogg"));

    mediaPlayer->play();

    connect(mediaPlayer, &QMediaPlayer::playbackStateChanged, this, [=](QMediaPlayer::PlaybackState state) {
        if (state == QMediaPlayer::StoppedState) {
            mediaPlayer->deleteLater();
            audioOutput->deleteLater();
            this->deleteLater();
            // trebali smo ovako da izbjegnemo seg fault
            QTimer::singleShot(0, this, &QObject::deleteLater);
        }
    });
}

void Enemy::move(){
    setPos(x(), y() + 10);
    handleScreenBorder();
}

void Enemy::fireProjectile() {}
