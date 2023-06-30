#pragma once
#include "collider/BoxCollider.h"
class StageWall :
    public BoxCollider
{
public:
    //コンストラクタ
    StageWall();
    //デストラクタ
    ~StageWall();

    //描画以外の更新を実装する
    void Update();

    //描画に関することを実装する
    void Draw()const;

};

