#pragma once
#include"Define.h"
#include"Collider/BoxCollider.h"

#define IMAGE_SHIFT_X 15 //画像ずらし用
#define IMAGE_SHIFT_Y 13 //画像ずらし用

enum ENEMY_STATE
{
    E_IDOL_RIGHT = 0,
    E_IDOL_LEFT,
    CHARGE_RIGHT, 
    CHARGE_LEFT, 
    E_FLY_RIGHT,
    E_FLY_LEFT,
    PARACHUTE_RIGHT,
    PARACHUTE_LEFT,
    DEATH_RIGHT,
    DEATH_LEFT
};
class Enemy :public BoxCollider
{
private:

    ENEMY_STATE enemy_state;
    float acs_left;   //左加速度
    float acs_right;  //右加速度
    int acs_up;     //上加速度
    int acs_down;   //下加速度

    int jump_int;   //上昇ボタン間隔
    int jump_combo;  //連打数
    int jump_cd;    //ジャンプ連打中に下に落ちる速度を遅らせる

    int frame;      //フレーム計測用

    int charge;     //風船を膨らませる時間
    int enemy_level;    //敵のレベル
    bool first_flg;     //敵が始めて風船を膨らませるか判断
    bool levelup_once;     //敵が始めて風船を膨らませるか判断
    int balloon;        //残り風船
    bool death_flg;      //死亡しているか判断
    int  death_acs;      //死亡中の落ち方制御

    float ref_y;            //反発用変数（ｙ）

    int wait_time;           //風船を膨らませる前か判断
    bool onfloor_flg;        //StageFloorの上かどうか
    bool onshare_flg;       //StageFloorの上ということを共有するかどうか
    bool move_right_flg;    //右移動中か判断
    bool move_left_flg;     //左移動中か判断
    bool jump_flg;          //ジャンプ中か判断
    bool para_flg;          //パラシュート状態か判断
    bool ref_once_left;     //反射制御用
    bool ref_once_right;    //反射制御用

    int enemy_image[20];   //敵画像
    int enemy_anim;    //敵アニメーション用
    int para_anim;    //敵アニメーション用
    int anim_boost;     //アニメーション加速用

    float last_move_x;    //移動方向保存用
    bool last_input;    //入力方向保存用(0=右　1=左)

public:

    //コンストラクタ
    Enemy(int x, int y, int level);

    //デストラクタ
    ~Enemy();

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


    //敵の風船を減らす
    void BalloonDec();

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

    //右入力
    void EnemyMoveRight();

    //左入力
    void EnemyMoveLeft();

    //右入力もしくは左入力をやめる
    void EnemyMoveStop();

    //ジャンプ入力
    void EnemyJump();

    //ジャンプ入力をやめる
    void EnemyJumpStop();

    //リセット
    void EnemyReset();

    //レベルアップ
    void EnemyLevelUp();

    //enemy_levelを取得
    int GetEnemyLevel()const { return enemy_level; }
};
