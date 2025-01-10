#include <Qtimer>
#include "ScreenConfig.h"
#include "FatMouseEnemy.h"

FatMouseEnemy::FatMouseEnemy(QGraphicsItem *parent, int max_health, int type) : Enemy(parent, max_health, type) {
    setPixmap(QPixmap(":/images/fattie_mis.png"));
    int random_number = abs(rand() % screenWidth - boundingRect().width());
    setPos(random_number,0);

    QTimer * timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Enemy::move);
    timer->start(2000);
}
