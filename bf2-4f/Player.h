#pragma once
#include"Define.h"
#include"Collider/BoxCollider.h"

enum PLAYER_STATE
{
     IDOL = 0,
     WALK_LEFT,
     WALK_RIGHT,
     FLY_LEFT,
     FLY_RIGHT,
     DEATH
};
class Player :public BoxCollider
{
private:
    PLAYER_STATE player_state;
    //float x, y;   //BoxColliderが出来たら対応する変数に差し替え
    int acs_left;   //左加速度
    int acs_right;  //右加速度
    int acs_up;     //上加速度
    int acs_down;   //下加速度
    int jump_int;   //上昇ボタン間隔
    int jump_combo;  //連打数
    int frame;      //フレーム計測用
    float ref_px;      //反発用変数（+ｘ）
    float ref_mx;      //反発用変数（-ｘ）
    float ref_y;      //反発用変数（ｙ）

    //反射実験用
    int b_x1, b_y1, b_x2, b_y2;
    int b_x3, b_y3, b_x4, b_y4;
    int b_x5, b_y5, b_x6, b_y6;
public:

    //コンストラクタ
    Player();

    //デストラクタ
    ~Player();

    //描画以外の更新を実行
    void Update();

    //描画に関することを実装
    void Draw() const;
};
