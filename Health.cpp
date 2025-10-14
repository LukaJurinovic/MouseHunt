#include "Health.h"

Health::Health(int max_health) {
    this->max_health = max_health;
    current_health = max_health;
}

void Health::change_health(int amount) {
    current_health += amount;
}

int Health::getHealth() const {
    return current_health;
}
