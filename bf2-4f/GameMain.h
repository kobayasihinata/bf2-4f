#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Enemy.h"
#include"StageFloor.h"
#include"StageWall.h"
#include"Fish.h"
#include"UI.h"

class GameMain :
    public AbstractScene
{
private:
    Player* player;
    Enemy* enemy;
    StageFloor* stagefloor[3];
    StageWall* staegwall;
    Fish* fish;
    UI* ui;

    int seaImage;
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

