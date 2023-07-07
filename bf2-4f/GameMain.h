#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include"StageFloor.h"
#include"StageWall.h"
#include"Pause.h"

class GameMain :
    public AbstractScene
{
private:
    Player* player;
    StageFloor* stagefloor;
    StageWall* staegwall;
    bool Pouse;
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

