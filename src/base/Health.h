#ifndef HEALTH_H
#define HEALTH_H

class Health {
private:
    int current_health;
    int max_health;
public:
    explicit Health(int max_health);

    void damage(int amount);
    void heal(int amount);
    int getHealth() const;
    bool isDead() const;
};

#endif
