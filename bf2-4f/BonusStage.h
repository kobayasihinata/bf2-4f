#pragma once
#include "AbstractScene.h"
#include "GameMain.h"
#include "Player.h"
#include "UI.h"
#include "BackGroundStar.h"
#include "StageObject.h"
#include"Balloon.h"

#define ENEMY_NAMBER 6
#define SECOND_TO_FRAME(sec) ((sec)*FRAMERATE)
#define MAX_FLOOR 7+3
#define MAX_STAR 40     //背景の星の最大数


class BonusStage :
    public AbstractScene
{
private:

    Player* player;
    StageObject* stageobject;
    UI* ui;
    Balloon* balloon[20];

    int spawn_int;              //フレーム数
    int get_balloon_count;      //風船を取得した数格納
    int spawn_balloon_count;    //風船を生成した数格納

    bool pause;             //一時停止
    bool result_flg;        //結果を表示する
    bool once;              //一回だけ行う用
    int result_time;    //演出用

    int score;  //このステージで獲得したスコア
    int wait_time;  //加算後の待機時間
    int player_image[31];   //プレイヤー画像
    int balloon_image[4];   //画像用変数
    //BGM
   // int Trip_BGM;	


public:

    //コンストラクタ
    BonusStage();

    //デストラクタ
    ~BonusStage() final;

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;

    //風船をスポーンさせる
    void SpawnBalloon();

    //風船が全部取得済みもしくは画面外まで上昇済みか調べる
    bool EndCheck();
};