#pragma once
#include"AbstractScene.h"

class Pause 
{
private:
    bool DrawMenu;
public:

    //コンストラクタ
    Pause();

    //デストラクタ
    ~Pause();

    //描画以外の更新を実行
    void Update();

    //描画に関することを実装
    void Draw() const ;

    bool PauseMenu();

    void NowPause();
};