#include <QTimer>
#include <QScreen>
#include <QApplication>
#include <QGraphicsTextItem>
#include <QFont>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "Game.h"
#include "ScreenConfig.h"
#include "FatMouseEnemy.h"
#include "HorizontalEnemyL.h"
#include "HorizontalEnemyR.h"
#include "CasterMouseEnemy.h"

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

    player = new Player(0, 10);
    player->setPos(screenWidth / 2 - player->boundingRect().width() / 2, screenHeight - player->boundingRect().height());
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);

    hudContainer = new QGraphicsRectItem();
    hudContainer->setRect(0, 0, screenWidth, 70);
    hudContainer->setBrush(QColor("dimgray"));
    hudContainer->setZValue(100);
    scene->addItem(hudContainer);

    show_health = new QGraphicsTextItem(hudContainer);
    show_health->setDefaultTextColor(Qt::black);
    show_health->setFont(QFont("times", 16));
    show_health->setPos(10, 20);
    update_health();

    show_score = new QGraphicsTextItem(hudContainer);
    show_score->setDefaultTextColor(Qt::black);
    show_score->setFont(QFont("times", 16));
    show_score->setPos(show_health->x() + show_health->boundingRect().width() + 20, 20);
    update_score();

    show_weapon = new QGraphicsTextItem(hudContainer);
    show_weapon->setDefaultTextColor(Qt::black);
    show_weapon->setFont(QFont("times", 16));
    show_weapon->setPos(show_score->x() + show_score->boundingRect().width() + 20, 20);
    update_weapon();

    exitButton = new QPushButton("X", this);
    exitButton->setFixedSize(40, 40);
    exitButton->move(screenWidth - exitButton->width() - 20, (hudContainer->rect().height() - exitButton->height()) / 2);
    exitButton->show();
    exitButton->setFocusPolicy(Qt::NoFocus);

    connect(exitButton, &QPushButton::clicked, this, &QApplication::quit);

    hudContainer->setPos(0, 0);

    spawn<FatMouseEnemy>(3000);
    spawn<HorizontalEnemyL>(10000);
    spawn<HorizontalEnemyR>(10000);
    spawn<CasterMouseEnemy>(7000);

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

void Game::update_weapon() {
    show_weapon->setPlainText(QString("Weapon: ") + player->getWeaponName());
}

