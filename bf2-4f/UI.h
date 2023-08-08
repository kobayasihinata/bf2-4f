#pragma once

class UI
{
private:
	int high_score;

	int UI_image1;
	int UI_image2;
	int numbers_image[10];	//数字の画像
public:		    
	UI();  
	~UI();
	void Draw()const;
	//数字の描画(UI.hとcppに書くのもあり)
	void DrawNumber(int x, int y, int score)const;

	//ハイスコアの読込
	void ReadHighScore();

	//ハイスコアの保存
	void SaveHighScore();
};