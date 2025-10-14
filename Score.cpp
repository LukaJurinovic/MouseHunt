#include "Score.h"

Score::Score(){
    score = 0;
}

void Score::increase(int amount) {
    score += amount;
}

int Score::getScore() const {
    return score;
}
