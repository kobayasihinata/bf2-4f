#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include"StageFloor.h"
#include"StageWall.h"
#include"Fish.h"

class GameMain :
    public AbstractScene
{
private:
    Player* player;
    StageFloor* stagefloor[3];
    StageWall* staegwall;
    Fish* fish;

    int seaImage;

public:

    //コンストラクタ
    GameMain();

    //デストラクタ
    ~GameMain() final;

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;
};

