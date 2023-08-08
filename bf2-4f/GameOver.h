#pragma once
#include "AbstractScene.h"

#define SECOND_TO_FRAME(sec) ((sec)*60)

class GameOver :
    public AbstractScene
{
private:
    int GameOver_Img;
    int WaitTimer;
public:

    //コンストラクタ
    GameOver();

    //デストラクタ
    ~GameOver();

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;
};
