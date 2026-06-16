#include "Weapon.h"
#include "Weapons.h"

Projectile* GunWeapon::createProjectile() const {
    return new Bullet();
}

Projectile* CheeseWeapon::createProjectile() const {
    return new Cheese();
}

Projectile* MouseTrapWeapon::createProjectile() const {
    return new MouseTrap();
}
