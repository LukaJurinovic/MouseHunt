#ifndef WEAPON_H
#define WEAPON_H

#include <QString>
#include <QPointF>

class Projectile;

class Weapon {
public:
    virtual ~Weapon() = default;

    virtual Projectile* createProjectile() const = 0;
    virtual QString name() const = 0;
    virtual QString playerPixmap() const = 0;
    virtual QString hudIconPath() const = 0;
    virtual QPointF hudIconOffset() const = 0;
    virtual QPointF muzzleOffset() const = 0;
};

class GunWeapon : public Weapon {
public:
    Projectile* createProjectile() const override;
    QString name() const override { return "Gun"; }
    QString playerPixmap() const override { return ":/images/evil_cat_with_gun.png"; }
    QString hudIconPath() const override { return ":/images/desert_eagle.png"; }
    QPointF hudIconOffset() const override { return QPointF(40, 5); }
    QPointF muzzleOffset() const override { return QPointF(180, 0); }
};

class CheeseWeapon : public Weapon {
public:
    Projectile* createProjectile() const override;
    QString name() const override { return "Cheese"; }
    QString playerPixmap() const override { return ":/images/evil_cat.png"; }
    QString hudIconPath() const override { return ":/images/cheese.png"; }
    QPointF hudIconOffset() const override { return QPointF(10, -35); }
    QPointF muzzleOffset() const override { return QPointF(42, 0); }
};

class MouseTrapWeapon : public Weapon {
public:
    Projectile* createProjectile() const override;
    QString name() const override { return "Mouse Trap"; }
    QString playerPixmap() const override { return ":/images/evil_cat.png"; }
    QString hudIconPath() const override { return ":/images/mouse_trap.png"; }
    QPointF hudIconOffset() const override { return QPointF(40, -10); }
    QPointF muzzleOffset() const override { return QPointF(42, 0); }
};

#endif
