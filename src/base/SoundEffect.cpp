#include "SoundEffect.h"

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>

SoundEffect::SoundEffect(const QString& source, QObject* parent, qreal volume)
    : QObject(parent) {
    m_output = new QAudioOutput(this);
    m_output->setVolume(volume);
    m_player = new QMediaPlayer(this);
    m_player->setAudioOutput(m_output);
    m_player->setSource(QUrl(source));
}

void SoundEffect::play() {
    if (m_player->playbackState() == QMediaPlayer::PlayingState)
        m_player->setPosition(0);
    else
        m_player->play();
}

void SoundEffect::playOnce(const QString& source, qreal volume) {
    QMediaPlayer* player = new QMediaPlayer();
    QAudioOutput* output = new QAudioOutput();
    output->setVolume(volume);
    player->setAudioOutput(output);
    player->setSource(QUrl(source));

    QObject::connect(player, &QMediaPlayer::playbackStateChanged, player,
                     [player, output](QMediaPlayer::PlaybackState state) {
                         if (state == QMediaPlayer::StoppedState) {
                             player->deleteLater();
                             output->deleteLater();
                         }
                     });
    player->play();
}
