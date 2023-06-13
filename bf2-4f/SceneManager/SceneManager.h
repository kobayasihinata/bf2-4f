#pragma once
#include "AbstractScene.h"
class SceneManager:
    public AbstractScene
{
private:
    //コンストラクタ
    SceneManager(AbstractScene* scene) :mScene(scene) {};

    static SceneManager* instance;
    AbstractScene* mScene;
public:

    //デストラクタ
    ~SceneManager();
   

    //描画以外の更新を実行
    AbstractScene* Update() override;

    //描画に関することを実装
    void Draw() const override;

    //シングルトン
    static SceneManager* Create(AbstractScene* scene);
    static SceneManager* GetInstance();
    static void Delete();
};

