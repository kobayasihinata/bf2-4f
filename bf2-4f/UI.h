#pragma once

class UI
{
private:
	int UI_image1;
	int UI_image2;

	int numbers_image[10];	//�����̉摜
public:		    
	UI();  
	~UI();
	void Draw()const;
	//�����̕`��(UI.h��cpp�ɏ����̂�����)
	void DrawNumber(int x, int y, int score)const;

};