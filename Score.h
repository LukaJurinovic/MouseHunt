#ifndef SCORE_H
#define SCORE_H

class Score {
private:
    int score;
public:
    Score();

    void increase(int amount);
    int getScore() const;
};

#endif // SCORE_H
