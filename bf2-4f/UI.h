#pragma once

class UI
{
private:
	int high_score;

	int highscore_image;
	int score_image;
	int player_life_image;
	int numbers_image[10];	//�����̉摜
public:		    
	UI();  
	~UI();
	void Draw(int life)const;

	//�����̕`��
	void DrawNumber(int x, int y, int score,int wordcount)const;

	//�n�C�X�R�A�̓Ǎ�
	void ReadHighScore();

	//�n�C�X�R�A�̕ۑ�
	void SaveHighScore();
};