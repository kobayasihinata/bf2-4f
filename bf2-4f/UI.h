#pragma once

class UI
{
private:
	int high_score;

	int UI_image1;
	int UI_image2;
	int numbers_image[10];	//�����̉摜
public:		    
	UI();  
	~UI();
	void Draw()const;
	//�����̕`��(UI.h��cpp�ɏ����̂�����)
	void DrawNumber(int x, int y, int score)const;

	//�n�C�X�R�A�̓Ǎ�
	void ReadHighScore();

	//�n�C�X�R�A�̕ۑ�
	void SaveHighScore();
};