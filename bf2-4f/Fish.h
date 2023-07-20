#pragma once
#include "collider/BoxCollider.h"

#define SECOND_TO_FRAME(sec) ((sec)*60)
#define IMAGE_SHIFT 10       //画像調整用
#define SEASURFACE_START_X 158
#define SEASURFACE_END_X 480

class Fish :
    public BoxCollider
{
private:
    enum E_Fish_State
    {
        Rising_Fish_1 = 0,
        Rising_Fish_2,
        Rising_Fish_3,
        Falling_Fish_1,
        Falling_Fish_2,
        Falling_Fish_3,
        PreyingOn_Player,
        PreyingOn_Enemy_1,
        PreyingOn_Enemy_2,
        PreyingOn_Enemy_3,
    };
    int fish_image[10];                 //画像用
    int fish_state;                     //さかなの状態
    int probability;                    //確率
    int frame_count;                    //フレーム計測用
    int player_flying_on_sea_timer;     //プレイヤーが海面を飛んでいる時の計測用

    const float speed = 1.2f;           //速さ
    
    bool is_rising;                     //さかなが海から飛び上がっているか？
    bool is_falling;                    //さかなが海に落ちているか？
    bool is_preying_on_player;          //捕食しているのはプレイヤーか？
    bool is_preying_on_enemy;           //捕食しているのは敵か？
    bool reversal_flg;                  //画像は反転するか？
    bool respawn_flg;                   //プレイヤーをリスポーンさせるか？
    bool bubble_spawn_flg;

public:
    //コンストラクタ
    Fish();

    //デストラクタ
    ~Fish();

    //描画以外の更新を実装
    void Update();

    //描画に関することを実装
    void Draw()const;

    void TargetPrey(BoxCollider* boxcollider);

    bool CheckSeaSurface(BoxCollider* boxcollider);

    //is_preyed_on_playerの値を取得する
    bool GetIsPreyedOnPlayer() { return is_preying_on_player; }

    bool GetIsPreyedOnEnemyr() { return is_preying_on_enemy; }

    //respawn_flgの値を取得する
    bool GetRespawnFlg() { return respawn_flg; }

    //respawn_flgの値を引数に設定する
    void SetRespawnFlg(const bool flg) { respawn_flg = flg; }

    void NotAtSeaSurface();
};

