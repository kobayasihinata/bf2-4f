#pragma once
#include "collider/BoxCollider.h"

#define SECOND_TO_FRAME(sec) ((sec)*60)
#define IMAGE_SHIFT 10       //画像調整用
#define SEASURFACE_START_X 159
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

    float speed;                        //速さ
    
    bool is_rising;                     //さかなが海から飛び上がっているか？
    bool is_falling;                    //さかなが海に落ちているか？
    bool is_preyed_on_player;           //捕食したのはプレイヤーか？
    bool is_preyed_on_enemy;            //捕食したのは敵か？
    bool reversal_flg;                  //画像は反転するか？
    bool respawn_flg;                   //プレイヤーをリスポーンさせるか？

public:
    //コンストラクタ
    Fish();

    //デストラクタ
    ~Fish();

    //描画以外の更新を実装
    void Update(BoxCollider* boxcollider);

    //描画に関することを実装
    void Draw()const;

    //is_preyed_on_playerの値を取得する
    bool GetIsPreyedOnPlayer() { return is_preyed_on_player; }

    //respawn_flgの値を取得する
    bool GetRespawnFlg() { return respawn_flg; }

    //respawn_flgの値を引数に設定する
    void SetRespawnFlg(const bool flg) { respawn_flg = flg; }
};

