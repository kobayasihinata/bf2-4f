#pragma once
#include"DxLib.h"
#include"Define.h"
#include"Collider/BoxCollider.h"

class Balloon :public BoxCollider {
private:

    int flg;                //取られて消えた、もしくは画面外まで上がっていった時の判定
    int frame;              //フレーム数
    int balloon_anim;        //アニメーション用変数
    int acs_left;           //加速度左
    int acs_right;          //加速度右

	int balloon_image[4];   //画像用変数
	int get_balloon_se;   //風船取得時SE
public:
    //コンストラクタ
    Balloon(int x,int y);

    //デストラクタ
    ~Balloon();

    //描画以外の更新を実行
    void Update();

    //描画に関することを実装
    void Draw() const;

    //プレイヤーとの当たり判定処理
    int HitPlayerCollision(const BoxCollider* box_collider);

    //風船があるか取得
    int GetFlg() { return flg; }
};
