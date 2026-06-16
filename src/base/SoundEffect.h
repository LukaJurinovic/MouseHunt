#ifndef SOUNDEFFECT_H
#define SOUNDEFFECT_H

#include <QObject>
#include <QString>

class QMediaPlayer;
class QAudioOutput;

class SoundEffect : public QObject {
    Q_OBJECT
public:
    explicit SoundEffect(const QString& source, QObject* parent = nullptr, qreal volume = 1.0);

    void play();

    static void playOnce(const QString& source, qreal volume = 1.0);

private:
    QMediaPlayer* m_player;
    QAudioOutput* m_output;
};

#endif
