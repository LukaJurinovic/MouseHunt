#include "Projectile.h"
#include <QList>
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include "Enemy.h"
#include "Game.h"

extern Game* game;

Projectile::Projectile(QGraphicsItem* parent, int damage, int type) : Object2D(parent), damage(damage), type(type) {
    audioOutput = new QAudioOutput();
    audioOutput->setVolume(1);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Projectile::move);
    timer->start(50);
}

int Projectile::getDamage() const {
    return damage;
}

int Projectile::getType() const {
    return type;
}

void Projectile::playProjectileSound(){
    if (!weaponSound) return;
    weaponSound->setAudioOutput(audioOutput);
    if (weaponSound->playbackState() == QMediaPlayer::PlayingState) {
        weaponSound->setPosition(0);
    } else if (weaponSound->playbackState() == QMediaPlayer::StoppedState) {
        weaponSound->play();
    }
}

void Projectile::handleScreenBorder() {
    if (pos().y() < 0) {
        destroy();
        return;
    }
}

void Projectile::move() {
    handleScreenBorder();
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (QGraphicsItem* item : colliding_items) {
        if (Enemy* enemy = dynamic_cast<Enemy*>(item)) {
            if (enemy->getType() == getType()) {
                qDebug() << "test";
                if (getType() == 2 && enemy->getHealth() > getDamage()) {
                    qDebug() << "a tribalo je"; //neznan luka iden rucat, nmg gladan aj pls uberi ovo
                    QMediaPlayer* mediaPlayer = new QMediaPlayer(this);
                    QAudioOutput* audioOutput = new QAudioOutput(this);
                    mediaPlayer->setAudioOutput(audioOutput);
                    audioOutput->setVolume(1.0);
                    mediaPlayer->setSource(QUrl("qrc:/sounds/eating_sound.ogg"));
                    mediaPlayer->play();

                    connect(mediaPlayer, &QMediaPlayer::playbackStateChanged, mediaPlayer, [mediaPlayer, audioOutput](QMediaPlayer::PlaybackState state) {
                        if (state == QMediaPlayer::StoppedState) {
                            mediaPlayer->deleteLater();
                            audioOutput->deleteLater();
                        }
                    });
                }
                enemy->change_health(getDamage());
                if (enemy->getHealth() <= 0) {
                    enemy->destroy();
                    game->player->increase(1);
                    game->update_score();
                }
            }
            destroy();
            return;
        }
    }
    setPos(x(), y() - 20);
}

void Projectile::destroy() {
    if (timer) {
        timer->stop();
        timer->disconnect();
    }

    if (scene()) {
        scene()->removeItem(this);
    }

    QObject::deleteLater();
}
