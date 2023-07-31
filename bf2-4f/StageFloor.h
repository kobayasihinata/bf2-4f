#pragma once
#include "collider/BoxCollider.h"
class StageFloor :
    public BoxCollider
{
private:
    int shift;        //画像調整

    int landleft;
    int landleft2;
    int landright;
    int landright2;

    int footing1;
    int footing2;
    int footing3;
    int footing5;
    int footing6;

public:
    //コンストラクタ
    StageFloor(const int x, const int y,
        const int heigth, const int width, const int margin);
    //デストラクタ
    ~StageFloor();

    //描画以外の更新を実装する
    void Update();

    //描画に関することを実装する
    void Draw()const;

    //画像を表示させる
    void DrawLandLeft();
    void DrawLandRight();
    void DrawFooting1();
    void DrawFooting2();
    void DrawFooting3();
    void DrawFooting5();
    void DrawFooting6();
};

