#include "Hud.h"

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QFont>
#include <QColor>
#include "Player.h"
#include "Weapon.h"

static constexpr int kHudHeight = 70;

Hud::Hud(QGraphicsScene* scene, Player* player, int screenWidth) : m_player(player) {
    container = new QGraphicsRectItem();
    container->setRect(0, 0, screenWidth, kHudHeight);
    container->setBrush(QColor("dimgray"));
    container->setZValue(100);
    scene->addItem(container);

    healthText = new QGraphicsTextItem(container);
    healthText->setDefaultTextColor(Qt::black);
    healthText->setFont(QFont("times", 16));
    healthText->setPos(10, 20);
    updateHealth();

    scoreText = new QGraphicsTextItem(container);
    scoreText->setDefaultTextColor(Qt::black);
    scoreText->setFont(QFont("times", 16));
    scoreText->setPos(healthText->x() + healthText->boundingRect().width() + 20, 20);
    updateScore();

    weaponText = new QGraphicsTextItem(container);
    weaponText->setDefaultTextColor(Qt::black);
    weaponText->setFont(QFont("times", 16));
    weaponText->setPos(scoreText->x() + scoreText->boundingRect().width() + 30, 20);
    updateWeapon();

    weaponImage = new QGraphicsPixmapItem(container);
    updateWeaponImage(m_player->currentWeapon()->hudIconPath(),
                      m_player->currentWeapon()->hudIconOffset());

    container->setPos(0, 0);
}

void Hud::updateHealth() {
    healthText->setPlainText(QString("Health: ") + QString::number(m_player->getHealth()));
}

void Hud::updateScore() {
    scoreText->setPlainText(QString("Score: ") + QString::number(m_player->getScore()));
}

void Hud::updateWeapon() {
    weaponText->setPlainText(QString("Weapon: ") + m_player->getWeaponName());
}

void Hud::updateWeaponImage(const QString& path, const QPointF& offset) {
    weaponImage->setPixmap(QPixmap(path));
    weaponImage->setPos(weaponText->x() + weaponText->boundingRect().width() + offset.x(),
                        offset.y());
}
