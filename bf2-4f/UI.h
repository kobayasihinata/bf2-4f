#pragma once

class UI
{
public:
	mutable int gScore = 0;

public:
	int Score();		    
	UI();  
	~UI() {};
	void Update();
	void Draw()const;
	int UI_image1;
	int UI_image2;
	int UI_image3[10];
	int UI_image4;
	int UI_image5;
	int Score_image;  
	int frame;      //�t���[���v���p
	


	void AddScore(int point) { gScore += point; }
	int GetScore() { return gScore;}

	void SetFrame(const int value)
	{
		frame = 0;
	}

	//�����̕`��(UI.h��cpp�ɏ����̂�����)
	//void DrawNumber(int x, int y, int score)const;
};