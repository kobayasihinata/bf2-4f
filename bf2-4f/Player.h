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
    float acs_left;   //左加速度
    float acs_right;  //右加速度
    int acs_up;     //上加速度
    int acs_down;   //下加速度
    int land_acs_left;  //左加速度(地面にいるとき)
    int land_acs_right;  //右加速度(地面にいるとき)
    int jump_int;   //上昇ボタン間隔
    int jump_combo;  //連打数
    int frame;      //フレーム計測用
    float ref_y;      //反発用変数（ｙ）
    int balloon;        //残り風船
    int life;           //残機
    bool onfloor_flg;   //StageFloorの上かどうか
    bool onshare_flg;   //StageFloorの上ということを共有するかどうか
    bool ref_once1;
    bool ref_once2;
    bool respawn_flg;   //リスポーンするかどうか
public:

    //コンストラクタ
    Player();

    //デストラクタ
    ~Player();

    //描画以外の更新を実行
    void Update();

    //描画に関することを実装
    void Draw() const;

    //ステージのオブジェクトとの当たり判定処理
    void HitStageCollision(const BoxCollider* box_collider);

    //床の上かどうか判定
    bool IsOnFloor(const BoxCollider* box_collider)const;

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

    //onshare_flgの値を設定する
    void SetOnShareFlg(const bool flg) 
    { 
        onshare_flg = flg; 
        //onshare_flgがtrueならonfloor_flgもtrueになる
        if (onshare_flg == true)
        {
            onfloor_flg = true;
        }
    }
};
