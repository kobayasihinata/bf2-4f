#pragma once
#include "Collider/BoxCollider.h"

#define _USE_MATH_DEFINES

#define SECOND_TO_FRAME(sec) ((sec)*60)
#define THUNDER_BALL_IMAGE_SHIFT 5

enum Thunder_Ball_State
{
    Stop = 0,
    Move,
    Hit
}; 

class Thunder :
    public BoxCollider
{
private:
    int cloud_image[3];                 //雲の画像
    int thunder_image[6];               //雷の画像
    int thunder_ball_image[3];          //雷の玉の画像

    int cloud_anim;                     //雲のアニメーション
    int thunder_anim;                   //雷のアニメーション
    int thunder_ball_anim;              //雷の玉のアニメーション

    int anim_frame;                     //アニメーションを調整するフレーム
    int fire_timer;                     //雷を発射するまでの時間
    int preliminary_action_time;        //予備動作の時間

    float speed;                        //速さ
    float angle;                        //角度
    float move_x;                       //xの移動量
    float move_y;                       //yの移動量

    float cloud_x;                      //雲のx座標
    float cloud_y;                      //雲のy座標
    int thunder_direction;              //雷の方向
    int thunder_ball_state;             //雷の玉の状態
    int probability;                    //確率
    int frame_count;                    //フレーム計測用

    bool fire_flg;                      //雷を発射してる？
    bool thunder_ball_flg;              //雷の玉を発射する?
    bool is_fire_ready;                 //雷の準備はいい？
    bool thunder_direction_flg;         //雷の方向は決まってる？
    bool is_in_game;                    //ゲームに追加する？

    //SE
    static int CreateThunderSE;		//カミナリ生成SE

public:
    //コンストラクタ
    Thunder(float x, float y, bool flg);

    //デストラクタ
    ~Thunder();

    //描画に関すること以外の更新の実装
    void Update();

    //描画に関することの実装
    void Draw(bool flg)const;

    void ChangeAngle();

    void Reflection(const BoxCollider* boxcollider);

    bool HitPlayer(const class Player* player);

    void ReInitThunder();
};