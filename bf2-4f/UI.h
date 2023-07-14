#pragma once
class UI
{
public:
	mutable int gScore = 0;

public:
	void Init();
	int Score();		    //スコア計算
	void DrawScore();	    //スコア表示
	int LoadImages(void);   //画像読込処理
	int UI_image [30];

	void AddScore(int point) { gScore += point; }
	int GetScore() { return gScore;}
};