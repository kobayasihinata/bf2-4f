#pragma once
#include "AbstractScene.h"

class Stage : 
	public AbstractScene
{
private:
	int stagefloor;
	int landleft;
	int landleft2;
	int landright;
	int landright2;
	int sea;
	int footing1;
	int footing2;
	int footing3;
	int footing4;
	int footing5;
	int footing6;
	int footing7;
	int footing8;


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

