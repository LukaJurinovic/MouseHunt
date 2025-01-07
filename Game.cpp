#include <QTimer>
#include <QScreen>
#include <QApplication>
#include <QGraphicsTextItem>
#include <QFont>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "Game.h"
#include "ScreenConfig.h"
#include "Enemy.h"
#include "HorizontalEnemyL.h"
#include "HorizontalEnemyR.h"

Game::Game(QWidget *parent):QGraphicsView(parent) {

    //ovo su globalne varijable
    QSize size = QApplication::primaryScreen()->size();
    screenWidth=size.width();
    screenHeight=size.height();

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, screenWidth, screenHeight);
    setScene(scene);

    setBackgroundBrush(QBrush(QImage(":/images/background.png")));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(screenWidth, screenHeight);

    player = new Player(0, 3);
    player->setPos(screenWidth / 2, screenHeight * 5 / 6);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);

    show_health = new QGraphicsTextItem();
    show_health->setDefaultTextColor(Qt::red);
    show_health->setFont(QFont("times", 16));
    show_health->setPos(10, 10);
    scene->addItem(show_health);
    update_health();

    show_score = new QGraphicsTextItem();
    show_score->setDefaultTextColor(Qt::blue);
    show_score->setFont(QFont("times", 16));
    show_score->setPos(10, 35);
    scene->addItem(show_score);
    update_score();

    spawn<Enemy>(1000);
    spawn<HorizontalEnemyL>(5000);
    spawn<HorizontalEnemyR>(5000);

    QMediaPlayer* music = new QMediaPlayer(this);
    QAudioOutput* audioOutput = new QAudioOutput(this);
    music->setAudioOutput(audioOutput);
    music->setSource(QUrl("qrc:/sounds/bgsound.wav"));
    audioOutput->setVolume(0.5);
    music->setLoops(QMediaPlayer::Infinite);
    music->play();

    show();
}

// genericni enemy spawner
template <typename enemyType>
void Game::spawn(int period) {
    QTimer* timerEnemy = new QTimer(this);
    connect(timerEnemy, &QTimer::timeout, this, [this]() {
        enemyType* enemy = new enemyType();
        scene->addItem(enemy);
    });
    timerEnemy->start(period);
}

void Game::update_health() {
    show_health->setPlainText(QString("Health: ") + QString::number(player->getHealth()));
}

void Game::update_score() {
    show_score->setPlainText(QString("Score: ") + QString::number(player->getScore()));
}
