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
    THUNDER_DEATH,
    INVINCIBLE,
    SUBMERGED
};
class Player :public BoxCollider
{
private:

    PLAYER_STATE player_state;
    float acs_left;              //左加速度
    float acs_right;             //右加速度
    int acs_up;                  //上加速度
    int acs_down;                //下加速度
    int land_acs_left;           //左加速度(地面にいるとき)
    int land_acs_right;          //右加速度(地面にいるとき)
    bool walk_SE_flg;

    int jump_int;                //上昇ボタン間隔
    int jump_combo;              //連打数
    int jump_cd;                 //ジャンプ連打中に下に落ちる速度を遅らせる
    bool jump_flg;               //ジャンプ中か判断
    bool jump_SE_flg;

    int frame;                   //フレーム計測用
    bool death_flg;              //死亡しているか判断
    bool thunder_death_flg;      //雷で死亡しているか判断
    bool fall_SE_flg;
    bool Splash_SE_flg;
    bool Restart_SE_flg;
    int  death_acs;              //死亡中の落ち方制御
    int  death_wait;             //死亡後の待ち時間
    int  thunder_death_wait;     //死亡後の待ち時間
    bool  underwater_flg;        //水没中か判断
    int respawn;                 //リスポーン後の無敵中か判断
    bool onfloor_flg;            //StageFloorの上かどうか
    bool onshare_flg;            //StageFloorの上ということを共有するかどうか
    bool ref_once_left;          //左方向に一回だけ反射する
    bool ref_once_right;         //右方向に一回だけ反射する

    int player_image[31];   //プレイヤー画像
    int splash_image[3];   //プレイヤー画像
    int player_anim;        //プレイヤーアニメーション用
    int splash_anim;        //水没アニメーション用
    int turn_anim;          //水没アニメーション用
    int anim_boost;         //アニメーション加速用
    int jump_anim_boost;    //ジャンプ連打時アニメーション加速用
    float last_move_x;      //移動方向保存用
    int last_input;         //入力方向保存用(-1=左 0=どこも押していない　1=右)
    bool soundflg;         //サウンド用

 
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

    //敵との当たり判定処理 (1=敵が右に、プレイヤーが左方向に反射　2=敵が左に、プレイヤーが右方向に反射　3=敵が上に、プレイヤーが下方向に反射　4=敵が下に、プレイヤーが上方向に反射)
    int HitEnemyCollision(const BoxCollider* box_collider);

    //床の上かどうか判定
    bool IsOnFloor(const BoxCollider* box_collider)const;

    //床に着地する
    void OnFloor();

    //敵に当たった時（プレイヤーが上）
    void OnHitEnemy();

    //X方向に移動しているときに-X方向に反射する
    void ReflectionMX();

    //-X方向に移動しているときにX方向に反射する
    void ReflectionPX();

    //-Y方向に移動しているときにY方向に反射する
    void ReflectionPY();

    //Y方向に移動しているときに-Y方向に反射する
    void ReflectionMY();

    //プレイヤーの残機を取得する
    int GetPlayerLife();

    //プレイヤーの残機を設定する
    void SetPlayerLife(const int life);

    //プレイヤーが無敵中か取得する
    int GetPlayerRespawn() { return respawn; }

    //プレイヤーが死んでいる途中かを取得する
    int GetPlayerDeathFlg() { return death_flg; }

    int GetWalkFlg() { return walk_SE_flg; }
    int GetJumpFlg() { return jump_SE_flg; }
    int GetFallFlg() { return fall_SE_flg; }
    int GetSplashSEflg() { return Splash_SE_flg; }
    //プレイヤーリスポーン
    void PlayerRespawn(float x, float y);

    int GetRestartSEflg() { return Restart_SE_flg; }

    void ResetSEflg1() {
        walk_SE_flg = false;
    }
    void ResetSEflg2() {
        jump_SE_flg = false;
    }
    void ResetSEflg3() {
        fall_SE_flg = false;
    }
    void ResetSEflg4() {
        Splash_SE_flg = false;
    }
    void ResetSEflg5() {
        Restart_SE_flg = false;
    }

    //プレイヤーの風船を減らす
    void BalloonDec();

    //プレイヤーが溺死中状態か取得する
    bool GetUnderWaterFlg() { return underwater_flg; }

    //プレイヤーが雷死状態か取得する
    bool GetThunderDeathFlg() { return thunder_death_flg; }

    //プレイヤーを雷死状態に設定する
    void SetThunderDeath(bool flg) { thunder_death_flg = flg; }

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


    Location GetPlayerLocation() { return location; }

    int GetPlayerState() { return player_state; }

    void SetPlayerState(const PLAYER_STATE state) { player_state = state; }

    //プレイヤーを初期地点に移動させる
    void ResetPlayerPos(int x,int y);

    //プレイヤーの風船とライフをリセットする
    void ResetPlayerLife();
};
