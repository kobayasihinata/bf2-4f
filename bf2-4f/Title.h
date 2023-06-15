#pragma once
#include "AbstractScene.h"
#include"StageBox.h"

class Title :
    public AbstractScene
{
private:
    StageBox* stagebox;

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
