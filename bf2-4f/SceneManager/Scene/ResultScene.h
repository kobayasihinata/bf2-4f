#pragma once
#include "../../common.h"
#include "../AbstractScene.h"
class ResultScene :
    public AbstractScene
{
public:
    ResultScene(int score = 0, int kill_count = 0, int avoid_count = 0, int eat_count = 0);
    ~ResultScene();

    AbstractScene* Update();
    void Draw()const;

private:
    int imageBack;
    int imageEnemy;
    const int score;
    const int killCount;
    const int avoidCount;
    const int eatCount;
};

