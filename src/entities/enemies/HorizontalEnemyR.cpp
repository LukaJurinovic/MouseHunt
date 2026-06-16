#include <QTimer>
#include <QRandomGenerator>
#include "ScreenConfig.h"
#include "HorizontalEnemyR.h"

HorizontalEnemyR::HorizontalEnemyR(QGraphicsItem *parent, int max_health, int type) : Enemy(parent, max_health, type) {
    int y = QRandomGenerator::global()->bounded(70, screenHeight * 5 / 6 + 70);
    setPos(screenWidth, y);

    setPixmap(QPixmap(":/images/rat_right.png"));

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &HorizontalEnemyR::move);
    timer->start(50);
}

void HorizontalEnemyR::handleScreenBorder() {
    if (pos().x() < 0)
        Object2D::destroy();
}

void HorizontalEnemyR::move() {
    setPos(x() - 20, y());
    handleScreenBorder();
}
