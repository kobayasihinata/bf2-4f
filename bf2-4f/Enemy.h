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

    bool flg;   //敵を表示するか（生きているか）
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
    int damage;         //やられモーション中待機
    int protect;        //復活後一瞬だけ無敵(バグ解消のため)
    int wait_time;           //風船を膨らませる前の待機時間
    int wait_flg;           //風船を膨らませる前か判断
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
    int last_input;    //入力方向保存用(-1=左 0=どこも押していない　1=右)

    int test_score; //点数加算確認用

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

    //敵との当たり判定処理
    int HitEnemyCollision(const BoxCollider* box_collider);

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

    //Y方向に移動しているときに-Y方向に反射する
    void ReflectionMY();

    //ダメージを与えて敵の状態に対応した処理を行い、対応したスコアを返す
    int ApplyDamege();

    //敵の風船を減らす
    void BalloonDec();

    //敵を死亡モーションに移行させる
    void EnemyDeath();

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

    //flgの値をを設定する
    void SetFlg(const bool flg)
    {
        this->flg = flg;
    }

    /******************************
     AIで移動させるときに使う関数
     ******************************/
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
    /******************************/

    //リセット
    void EnemyReset();

    //レベルアップ
    void EnemyLevelUp();

    //enemy_levelを取得
    int GetEnemyLevel()const { return enemy_level; }

    //敵が死亡モーション中か取得
    int GetEnemyDeathFlg() { return death_flg; }

    //敵が生きているか取得
    int GetFlg() { return flg; }

    //敵が風船を膨らませる前か取得
    int GetWaitFlg() { return wait_flg; }

    //敵の位置を取得
    Location GetEnemyLocation() { return location; }
};
