#pragma once

#include<DxLib.h>
#include"Define.h"
#include"Collider/BoxCollider.h"



class SoapBubble :public BoxCollider
{
private:
    int flg;
    int bubble_image[4];    //画像用変数
    int frame;              //フレーム数
    int bubble_anim;        //アニメーション用変数
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

