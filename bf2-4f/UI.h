#pragma once

class UI
{
public:
	mutable int gScore = 0;

public:
	int Score();		    //スコア計算
	UI();   //画像読込処理
	~UI() {};
	void Draw()const;
	int UI_image1;
	int UI_image2;
	int UI_image3;
	int Score_image;
	int UI_image[10];   

	void AddScore(int point) { gScore += point; }
	int GetScore() { return gScore;}

};