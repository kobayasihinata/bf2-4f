#pragma once
#include "DxLib.h"

class AbstractScene
{
protected:
	int numbers_image[10];	//数字の画像
	int dammy = LoadDivGraph("images/UI/UI_NumAnimation.png", 10, 10, 1, 32, 32, numbers_image);
public:

	//デストラクタ
	virtual ~AbstractScene();

	//描画以外の更新
	virtual AbstractScene* Update() = 0;

	//描画の更新
	virtual void Draw() const = 0;

	//数字の描画(UI.hとcppに書くのも有り)
	void DrawNumber(int x, int y, int score)const;
};

