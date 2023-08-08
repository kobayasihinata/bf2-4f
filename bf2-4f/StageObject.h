#pragma once
#include "Collider/BoxCollider.h"

class StageObject :
    public BoxCollider
{
protected:
    int shift;        //画像調整

    static int landleft;
    static int landleft2;
    static int landright;
    static int landright2;

    static int footing1;
    static int footing2;
    static int footing3;
    static int footing5;
    static int footing6;

    static int footing4;
    static int footing7;
    static int footing8;

public:
    //コンストラクタ
    StageObject();

    //デストラクタ
    ~StageObject();

    //描画以外の更新を実装する
    void Update() {};

    //描画に関することを実装する
    void Draw()const {};

    void SetInit(int x, int y, int height, int width, int shift)
    {
        this->location.x = (float)x;
        this->location.y = (float)y + shift;
        this->area.height = (float)height;
        this->area.width = (float)width;
        this->shift = shift;
    }

};

