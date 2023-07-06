#pragma once
#include"Define.h"
#include"Collider/BoxCollider.h"

#define IMAGE_SHIFT_X 15 //画像ずらし用
#define IMAGE_SHIFT_Y 13 //画像ずらし用

enum PLAYER_STATE
{
     IDOL_RIGHT = 0,
     IDOL_LEFT,
     WALK_LEFT,
     TURN_LEFT,
     WALK_RIGHT,
     TURN_RIGHT,
     FLY_LEFT,
     FLY_RIGHT,
     DEATH,
     THUNDER_DEATH
};
class Player :public BoxCollider
{
private:

    PLAYER_STATE player_state;

    int acs_left;   //左加速度
    int acs_right;  //右加速度
    int acs_up;     //上加速度
    int acs_down;   //下加速度
    int land_acs_left;  //左加速度(地面にいるとき)
    int land_acs_right;  //右加速度(地面にいるとき)

    int jump_int;   //上昇ボタン間隔
    int jump_combo;  //連打数

    int frame;      //フレーム計測用

    int balloon;        //残り風船
    int life;            //残機
    bool death_flg;      //死亡しているか判断

    float ref_y;      //反発用変数（ｙ）
    bool onfloor_flg;   //StageFloorの上かどうか
    bool ref_once1;
    bool ref_once2;

    int player_image[30];   //プレイヤー画像
    int player_anim;    //プレイヤーアニメーション用
    int anim_boost;     //アニメーション加速用

    float last_move_x;    //移動方向保存用
    bool last_input;    //移動方向保存用(0=左　1=右)

public:

    //コンストラクタ
    Player();

    //デストラクタ
    ~Player();

    //描画以外の更新を実行
    void Update();

    //描画に関することを実装
    void Draw() const;

    //ステージのオブジェクトとの当たり判定
    void HitStageCollision(const BoxCollider* box_collider);

    //床に着地する
    void OnFloor();

    //X方向に移動しているときに-X方向に反射する
    void ReflectionMX();

    //-X方向に移動しているときにX方向に反射する
    void ReflectionPX();

    //-Y方向に移動しているときにY方向に反射する
    void ReflectionPY();

    //プレイヤーの残機を取得する
    int GetPlayerLife() { return life; }

    //プレイヤーリスポーン
    void PlayerRespawn(int x,int y);

    //プレイヤーの風船を減らす
    void BalloonDec();
};
