#pragma once
#include"AbstractScene.h"

class Pouse 
{
private:
    bool DrawMenu;
public:

    //コンストラクタ
    Pouse();

    //デストラクタ
    ~Pouse();

    //描画以外の更新を実行
    void Update();

    //描画に関することを実装
    void Draw() const ;

    bool PouseMenu();

    void NowPouse();
};