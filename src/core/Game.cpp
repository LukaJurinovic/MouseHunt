#include "Game.h"

#include <QApplication>
#include <QScreen>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "ScreenConfig.h"
#include "Hud.h"
#include "EnemySpawner.h"

static constexpr int kHudHeight = 70;

Game::Game(QWidget *parent) : QGraphicsView(parent) {
    QSize size = QApplication::primaryScreen()->size();
    screenWidth = size.width();
    screenHeight = size.height();

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, screenWidth, screenHeight);
    setScene(scene);

    setBackgroundBrush(QBrush(QImage(":/images/background.png")));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(screenWidth, screenHeight);

    player = new Player(0, 10);
    player->setPos(screenWidth / 2 - player->boundingRect().width() / 2,
                   screenHeight - player->boundingRect().height());
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);

    hud = new Hud(scene, player, screenWidth);

    exitButton = new QPushButton("X", this);
    exitButton->setFixedSize(40, 40);
    exitButton->move(screenWidth - exitButton->width() - 20, (kHudHeight - exitButton->height()) / 2);
    exitButton->show();
    exitButton->setFocusPolicy(Qt::NoFocus);
    connect(exitButton, &QPushButton::clicked, this, &QApplication::quit);

    spawner = new EnemySpawner(scene, this);
    spawner->start();

    QMediaPlayer* music = new QMediaPlayer(this);
    QAudioOutput* musicOutput = new QAudioOutput(this);
    music->setAudioOutput(musicOutput);
    music->setSource(QUrl("qrc:/sounds/bgsound.wav"));
    musicOutput->setVolume(0.5);
    music->setLoops(QMediaPlayer::Infinite);
    music->play();

    show();
}

void Game::update_health() {
    hud->updateHealth();
}

void Game::update_score() {
    hud->updateScore();
}

void Game::update_weapon() {
    hud->updateWeapon();
}

void Game::update_weapon_image(const QString& path, const QPointF& offset) {
    hud->updateWeaponImage(path, offset);
}
