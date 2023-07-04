#pragma once
#include "collider/BoxCollider.h"
class StageFloor :
    public BoxCollider
{
public:
    //コンストラクタ
    StageFloor();
    //デストラクタ
    ~StageFloor();

    //描画以外の更新を実装する
    void Update();

    //描画に関することを実装する
    void Draw()const;

};

