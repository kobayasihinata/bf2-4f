#pragma once
#include"AbstractScene.h"
class Pouse :
    public AbstractScene
{
private:
    bool DrawMenu;
public:

    //コンストラクタ
    Pouse();

    //デストラクタ
    ~Pouse() ;

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;
};