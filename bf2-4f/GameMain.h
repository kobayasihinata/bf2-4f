#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_AI.h"
#include"StageFloor.h"
#include"StageWall.h"
#include"Fish.h"
#include"SoapBubble.h"

class GameMain :
    public AbstractScene
{
private:
    Player* player;
    Enemy* enemy[4];
    ENEMY_AI* enemy_ai[4];
    StageFloor* stagefloor[3];
    StageWall* staegwall;
    Fish* fish;
    SoapBubble* soapbubble[4];

    int seaImage;
    bool Pouse;
    int score;  //仮のスコア格納場所
    int max_enemy;      //敵の数
    int P_x, P_y;       //プレイヤー座標
    const int Enemy_Move_Cool[3]{ 120,80,40 };
    int move_cooltime;

public:

    //コンストラクタ
    GameMain();

    //デストラクタ
    ~GameMain() final;

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;

    //敵とプレイヤーが接触した時のダメージ処理
    void Damege(int i);
};

