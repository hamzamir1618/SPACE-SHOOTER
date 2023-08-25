#ifndef SCORE_H
#define SCORE_H
#include <iostream>
#include <string.h>
using namespace std;
class Score
{
public:
    int score;
    Score()
    {
        score = 0;
    }

    string getScoreString()
    {

        return to_string(score);
    }
};

#endif