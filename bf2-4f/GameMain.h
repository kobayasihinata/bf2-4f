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

#define ENEMY_NAMBER 6
#define FLOOR_MAX 7

class GameMain :
    public AbstractScene
{
private:
    Player* player;
    Enemy* enemy[ENEMY_NAMBER];
    ENEMY_AI* enemy_ai[ENEMY_NAMBER];
    StageFloor* stagefloor[FLOOR_MAX];
    //StageWall* staegwall;
    Fish* fish;
    Thunder* thunder;
    SoapBubble* soapbubble[6];

    int seaImage;
    bool Pouse;
    int score;  //仮のスコア格納場所
    int max_enemy;      //敵の数
    int P_x, P_y;       //プレイヤー座標
    bool Avoidance[ENEMY_NAMBER]; // 回避フラグ
    bool damage_once;   //重なっている時一回だけダメージを与える
    int now_floor_max;  //現在の床の数

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

