#pragma once

class UI
{
private:
	int UI_image1;
	int UI_image2;

	int numbers_image[10];	//数字の画像
public:		    
	UI();  
	~UI();
	void Draw()const;
	//数字の描画(UI.hとcppに書くのもあり)
	void DrawNumber(int x, int y, int score)const;

};