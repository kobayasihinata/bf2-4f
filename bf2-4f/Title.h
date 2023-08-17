#pragma once
#include "AbstractScene.h"

#define TITLEMODESELECT_X 165
#define TITLEMODESELECT_Y 270

class Title :
    public AbstractScene
{
private:
    int titlelogo;
    int titlecredit;
    int titlemodeselect;
    int titlecursor[4];

    int cursor_y;
    int cursor_num;
    int interval;
    int cursor_anim;
    int frame;
public:

    //コンストラクタ
    Title();

    //デストラクタ
    ~Title() final;

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;
};
