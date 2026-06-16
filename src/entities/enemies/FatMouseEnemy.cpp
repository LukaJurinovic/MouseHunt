#include <QTimer>
#include <QRandomGenerator>
#include "ScreenConfig.h"
#include "FatMouseEnemy.h"

FatMouseEnemy::FatMouseEnemy(QGraphicsItem *parent, int max_health, int type) : Enemy(parent, max_health, type) {
    setPixmap(QPixmap(":/images/fat_mouse.png"));
    int maxX = qMax(1, static_cast<int>(screenWidth - boundingRect().width()));
    setPos(QRandomGenerator::global()->bounded(maxX), 0);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Enemy::move);
    timer->start(2000);
}

void FatMouseEnemy::move() {
    if (!sleeping) {
        setPos(x(), y() + 6);
        handleScreenBorder();
    }
}
