#pragma once
#include"Dxlib.h"
#include"Define.h"
#include"Location.h"

class BackGroundStar
{
private:
	int type;			//星の色タイプ
    Location star_pos;	//星の描画位置
    int star_color;		//星の色
    int star_drawtime;  //星の位置更新までの時間

public:
	//コンストラクタ
	BackGroundStar(int stage);

	//デストラクタ
	~BackGroundStar();

	//描画以外の処理
	void Update();

	//描画処理
	void Draw()const;

	//星の色を抽選する
	void SetColor(int type);

	//現在のステージ数を受け取る
	void GetType(int stage) { type = stage; }
};
