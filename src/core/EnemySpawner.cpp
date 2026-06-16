#include "EnemySpawner.h"

#include <QGraphicsScene>
#include "Enemy.h"
#include "FatMouseEnemy.h"
#include "HorizontalEnemyL.h"
#include "HorizontalEnemyR.h"
#include "CasterMouseEnemy.h"

EnemySpawner::EnemySpawner(QGraphicsScene* scene, QObject* parent)
    : QObject(parent), m_scene(scene) {}

void EnemySpawner::start() {
    spawn<FatMouseEnemy>(4000);
    spawn<Enemy>(7000);
    spawn<HorizontalEnemyL>(15000);
    spawn<HorizontalEnemyR>(10000);
    spawn<CasterMouseEnemy>(12000);
}
