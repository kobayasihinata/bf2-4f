#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Enemy.h"
#include"StageFloor.h"
#include"StageWall.h"
#include"Fish.h"

class GameMain :
    public AbstractScene
{
private:
    Player* player;
    Enemy* enemy[3];
    StageFloor* stagefloor[3];
    StageWall* staegwall;
    Fish* fish;

    int seaImage;
    bool Pouse;

    int score;  //仮のスコア格納場所

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

