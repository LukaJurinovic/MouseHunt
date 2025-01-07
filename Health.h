#ifndef HEALTH_H
#define HEALTH_H

class Health {
private:
    int current_health, max_health;
public:
    Health(int max_health);
    void change_health(int amount);
    int getHealth() const;
};

#endif // HEALTH_H
