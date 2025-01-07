QT       += core gui\
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Enemy.cpp \
    Entity.cpp \
    Game.cpp \
    Health.cpp \
    HorizontalEnemyL.cpp \
    HorizontalEnemyR.cpp \
    Object2D.cpp \
    Player.cpp \
    Projectile.cpp \
    Score.cpp \
    ScreenConfig.cpp \
    Weapons.cpp \
    main.cpp

HEADERS += \
    Enemy.h \
    Entity.h \
    Game.h \
    Health.h \
    HorizontalEnemyL.h \
    HorizontalEnemyR.h \
    Object2D.h \
    Player.h \
    Projectile.h \
    Score.h \
    ScreenConfig.h \
    Weapons.h \

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    background.png \
    bgsound.wav \
    bullet.png \
    bullet.wav \
    enemy.png \
    mis.png \
    player.png
