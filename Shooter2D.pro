QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += \
    src \
    src/core \
    src/base \
    src/entities \
    src/entities/enemies \
    src/player \
    src/weapons

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/core/Game.cpp \
    src/core/ScreenConfig.cpp \
    src/core/Hud.cpp \
    src/core/EnemySpawner.cpp \
    src/base/Object2D.cpp \
    src/base/Health.cpp \
    src/base/SoundEffect.cpp \
    src/entities/Entity.cpp \
    src/entities/enemies/Enemy.cpp \
    src/entities/enemies/CasterMouseEnemy.cpp \
    src/entities/enemies/FatMouseEnemy.cpp \
    src/entities/enemies/HorizontalEnemyL.cpp \
    src/entities/enemies/HorizontalEnemyR.cpp \
    src/player/Player.cpp \
    src/player/Score.cpp \
    src/weapons/Projectile.cpp \
    src/weapons/Weapon.cpp \
    src/weapons/Weapons.cpp

HEADERS += \
    src/core/Game.h \
    src/core/ScreenConfig.h \
    src/core/Hud.h \
    src/core/EnemySpawner.h \
    src/base/Object2D.h \
    src/base/Health.h \
    src/base/SoundEffect.h \
    src/entities/Entity.h \
    src/entities/enemies/Enemy.h \
    src/entities/enemies/CasterMouseEnemy.h \
    src/entities/enemies/FatMouseEnemy.h \
    src/entities/enemies/HorizontalEnemyL.h \
    src/entities/enemies/HorizontalEnemyR.h \
    src/player/Player.h \
    src/player/Score.h \
    src/weapons/Projectile.h \
    src/weapons/Weapon.h \
    src/weapons/Weapons.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    README.md
