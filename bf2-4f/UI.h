#pragma once

class UI
{
public:
	mutable int gScore = 0;

public:
	int Score();		    
	UI();  
	~UI() {};
	void Draw()const;
	int UI_image1;
	int UI_image2;
	int UI_image3[10];
	int UI_image4;
	int UI_image5;
	int UI_image6;
	int Score_image;  

	void AddScore(int point) { gScore += point; }
	int GetScore() { return gScore;}

	//数字の描画(UI.hとcppに書くのもあり)
	//void DrawNumber(int x, int y, int score)const;
};