#pragma once

class UI
{
private:
	int high_score;

	int highscore_image;
	int score_image;
	int player_life_image;
	int numbers_image[10];	//数字の画像
public:		    
	UI();  
	~UI();
	void Draw(int life)const;

	//数字の描画
	void DrawNumber(int x, int y, int score,int wordcount)const;

	//ハイスコアの読込
	void ReadHighScore();

	//ハイスコアの保存
	void SaveHighScore();
};