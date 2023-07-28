#pragma once
#include "collider/BoxCollider.h"
class StageWall :
    public BoxCollider
{
private:
    int shift;

    int footing4;
    int footing7;
    int footing8;

public:
    //コンストラクタ
    StageWall(int x, int y, int height, int width, int shift);
    //デストラクタ
    ~StageWall();

    //描画以外の更新を実装する
    void Update();

    //描画に関することを実装する
    void Draw()const;

    void DrawFooting4();
    void DrawFooting7();
    void DrawFooting8();


};

