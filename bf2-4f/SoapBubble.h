#pragma once

#include<DxLib.h>
#include"Define.h"
#include"Collider/BoxCollider.h"

class SoapBubble :public BoxCollider
{
private:
    int flg;
    int bubble_image[4];    //画像用変数
    int getscore_image;     //スコア獲得画像
    int getscore_anim;    //スコア獲得演出画像表示用
    int getscore_x;         //スコア獲得演出用X座標
    int getscore_y;         //スコア獲得演出用Y座標
    bool is_getscore;    //スコア獲得時演出用
    int frame;              //フレーム数
    int bubble_anim;        //アニメーション用変数
    int acs_left;           //加速度左
    int acs_right;          //加速度右
    int bubble_get_anim;    //シャボン玉取得時アニメーション
    bool get_once;           //何回もシャボン玉を取れるバグ解消(臨時)

    //SE
    int GetSoupBubble_SE;	//シャボン玉破裂SE

    
public:

    //コンストラクタ
    SoapBubble();

    //デストラクタ
    ~SoapBubble();

    //描画以外の更新を実行
    void Update();

    //描画に関することを実装
    void Draw() const;

    //プレイヤーとの当たり判定処理
    int HitPlayerCollision(const BoxCollider* box_collider);

    //シャボン玉をスポーンさせる
    void SoapBubbleSpawn(int x);
};

