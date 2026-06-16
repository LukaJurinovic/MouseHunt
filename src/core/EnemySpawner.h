#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include <QObject>
#include <QTimer>

class QGraphicsScene;

class EnemySpawner : public QObject {
public:
    explicit EnemySpawner(QGraphicsScene* scene, QObject* parent = nullptr);
    void start();

private:
    template <typename EnemyType>
    void spawn(int periodMs);

    QGraphicsScene* m_scene;
};

template <typename EnemyType>
void EnemySpawner::spawn(int periodMs) {
    QTimer* timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, [this]() {
        m_scene->addItem(new EnemyType());
    });
    timer->start(periodMs);
}

#endif
