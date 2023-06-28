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
    int acs_left;   //左加速度
    int acs_right;  //右加速度
    int acs_up;     //上加速度
    int acs_down;   //下加速度
    int land_acs_left;  //左加速度(地面にいるとき)
    int land_acs_right;  //右加速度(地面にいるとき)
    int jump_int;   //上昇ボタン間隔
    int jump_combo;  //連打数
    int frame;      //フレーム計測用
    float ref_y;      //反発用変数（ｙ）
    int life;         //残機

    bool isOnFloor;     //デバッグ用

    //反射実験用
    int b_x1, b_y1, b_x2, b_y2;
    int b_x3, b_y3, b_x4, b_y4;
    int b_x5, b_y5, b_x6, b_y6;
    bool ref_once1;
    bool ref_once2;
public:

    //コンストラクタ
    Player();

    //デストラクタ
    ~Player();

    //描画以外の更新を実行
    void Update();

    //描画に関することを実装
    void Draw() const;

    bool GetOnFloor()
    {
        return &isOnFloor;
    }

    bool SetOnFloor(bool flg)
    {
        isOnFloor = flg;
        return isOnFloor;
    }
   
    void OnHitCollision(const BoxCollider* box_collider);
    void HitCollision(const BoxCollider* box_collider);


    //X方向に移動しているときに-X方向に反射する
    void ReflectionMX();

    //-X方向に移動しているときにX方向に反射する
    void ReflectionPX();

    //-Y方向に移動しているときにY方向に反射する
    void ReflectionPY();
};
