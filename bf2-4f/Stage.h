#pragma once
#include "AbstractScene.h"

class Stage : public AbstractScene
{
private:
	int stageimage;


public:
	//コンストラクタ
	Stage();
	//デストラクタ
	~Stage();

	//描画以外の処理
	AbstractScene* Update()override;

	//描画処理
	void Draw()const override;

};

