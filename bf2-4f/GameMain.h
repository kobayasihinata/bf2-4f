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

#define ENEMY_NAMBER 6
#define MAX_FLOOR 7
#define MAX_WALL 3

class GameMain :
    public AbstractScene
{
private:
    Player* player;
    Enemy* enemy[ENEMY_NAMBER];
    ENEMY_AI* enemy_ai[ENEMY_NAMBER];
    StageFloor* stagefloor[MAX_FLOOR];
    StageWall* stagewall[MAX_WALL];
    Fish* fish;
    Thunder* thunder;
    SoapBubble* soapbubble[6];
    UI* ui;

    int stage;      //現在のステージ数
    int seaImage;
    int GameStart_BGM;
    int EnemuyMove_SE;
    bool Pouse;
    int max_enemy;      //敵の数
    int now_floor_max;      //床の数
    int P_x, P_y;       //プレイヤー座標
    bool Avoidance[ENEMY_NAMBER]; // 回避フラグ
    bool damage_once;   //重なっている時一回だけダメージを与える
    bool clear_flg;     //次のステージへ遷移する条件を調べる用
    int clear_wait;     //次のステージへ遷移する前の待ち時間

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

    //次のステージへ
    int NextStage();

    //敵と地面を生成する
    void CreateStage(int stage);

    //点数取得
    static int GetScore();

    //敵のスポーン位置を指定した床の上に設定
    Location SpawnPosSet(StageFloor* floor);
    Location SpawnPosSet(StageWall* wall);
};

