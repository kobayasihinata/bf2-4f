#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy_AI.h"
#include"StageObject.h"
#include"Fish.h"
#include"SoapBubble.h"
#include"Thunder.h"
#include"UI.h"
#include"SoundManager.h"
#include"BackGroundStar.h"

#define ENEMY_NAMBER 6
#define SECOND_TO_FRAME(sec) ((sec)*FRAMERATE)
#define MAX_FLOOR 7+3
#define MAX_STAR 40     //背景の星の最大数

enum State {
    Normal,
    Clear,
    Over,
};

class GameMain :
    public AbstractScene
{
private:

    Player* player;
    Enemy* enemy[ENEMY_NAMBER];
    ENEMY_AI* enemy_ai[ENEMY_NAMBER];
    StageObject* stageobject[MAX_FLOOR];
    Fish* fish;
    Thunder* thunder[2];
    SoapBubble* soapbubble[6];
    UI* ui;
    SoundManager* soundmanager;
    BackGroundStar* backgroundstar[MAX_STAR];

    int seaImage;

    bool para;
    bool E_jump;

    bool Pouse;
    int max_enemy;      //敵の数
    int P_x, P_y;       //プレイヤー座標
    int AI_Pattern[ENEMY_NAMBER];     //Aiパターン
    bool Avoidance[ENEMY_NAMBER]; // 回避フラグ
    bool damage_once;   //重なっている時一回だけダメージを与える
    int main_state;
    bool clear_flg;     //次のステージへ遷移する条件を調べる用
    int clear_wait;     //次のステージへ遷移する前の待ち時間
    int now_floor_max;  //現在の床の数
    int GameOver_Img;   //ゲームオーバー画像  
    int phase_image;    //ステージ数表示画像
    int GameOver_BGM;   //ゲームオーバーBGM
    int WaitTimer;
    int phase_disptime; //ステージ数画像表示時間測定用
    int phase_disp;     //ステージ数画像表示点滅用

    //BGM
    int Continue_BGM;			//コンテニューBGM
    int StageClear_BGM;			//ステージクリアBGM

    //SE
    int EnemuyMove_SE;          //トリ鳴き声SE
    int BaloonBurst_SE;			//バルーン破裂SE
    int Eatable_SE;
    int StageClear_SE;
    int para_SE;
    int EnemyMove_SE;
    

    

public:

    //コンストラクタ
    GameMain(int beforescene);

    //デストラクタ
    ~GameMain() final;

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;

    //敵とプレイヤーが接触した時のダメージ処理
    void Damage(int i);

    //次のステージへ
    void NextStage();

    //敵と地面を生成する
    void CreateStage(int stage);

    //点数取得
    static int GetScore();

    //敵のスポーン位置を指定した床の上に設定
    Location SpawnPosSet(StageObject* floor);

    //データリセット
    static void DataReset();

    //スコア加算
    static void AddScore(int point);

};

