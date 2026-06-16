#include "Health.h"

#include <algorithm>

Health::Health(int max_health) : current_health(max_health), max_health(max_health) {}

void Health::damage(int amount) {
    current_health -= amount;
}

void Health::heal(int amount) {
    current_health = std::min(current_health + amount, max_health);
}

int Health::getHealth() const {
    return current_health;
}

bool Health::isDead() const {
    return current_health <= 0;
}
