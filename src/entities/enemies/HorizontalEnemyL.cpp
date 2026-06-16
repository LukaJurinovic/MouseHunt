#include <QTimer>
#include <QRandomGenerator>
#include "ScreenConfig.h"
#include "HorizontalEnemyL.h"

HorizontalEnemyL::HorizontalEnemyL(QGraphicsItem *parent, int max_health, int type) : Enemy(parent, max_health, type) {
    int y = QRandomGenerator::global()->bounded(70, screenHeight * 5 / 6 + 70);
    setPos(0, y);

    setPixmap(QPixmap(":/images/rat_left.png"));

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &HorizontalEnemyL::move);
    timer->start(50);
}

void HorizontalEnemyL::handleScreenBorder() {
    if (pos().x() > screenWidth)
        Object2D::destroy();
}

void HorizontalEnemyL::move() {
    setPos(x() + 20, y());
    handleScreenBorder();
}
