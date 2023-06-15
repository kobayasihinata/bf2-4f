#pragma once
#include"Define.h"

class Player 
{
private:
    short x, y;   //BoxColliderが出来たら対応する変数に差し替え
    int acs_left;   //左加速度
    int acs_right;  //右加速度
    int acs_up;     //上加速度
public:

    //コンストラクタ
    Player();

    //デストラクタ
    ~Player();

    //描画以外の更新を実行
    void Update();

    //描画に関することを実装
    void Draw() const;
};
