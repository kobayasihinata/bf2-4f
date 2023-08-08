#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_AI.h"
#include"StageFloor.h"
#include"StageWall.h"
#include"Fish.h"
#include"SoapBubble.h"
#include"Thunder.h"
#include"UI.h"

class GameMain :
    public AbstractScene
{
private:
    Player* player;
    Enemy* enemy[6];
    ENEMY_AI* enemy_ai[6];
    StageFloor* stagefloor[3];
    //StageWall* staegwall;
    Fish* fish;
    Thunder* thunder;
    SoapBubble* soapbubble[6];
    UI* ui;

    int seaImage;
    bool Pouse;
    int score;  //仮のスコア格納場所
    int max_enemy;      //敵の数
    int P_x, P_y;       //プレイヤー座標
    const int Enemy_Move_Cool[3]{ 360,240,120 };
    int move_cooltime;
    bool damage_once;   //重なっている時一回だけダメージを与える

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
    void Damage(int i);
};

