#pragma once

class UI
{
private:
	int UI_image1;
	int UI_image2;

	int numbers_image[10];	//”š‚Ì‰æ‘œ
public:		    
	UI();  
	~UI();
	void Draw()const;
	//”š‚Ì•`‰æ(UI.h‚Æcpp‚É‘‚­‚Ì‚à‚ ‚è)
	void DrawNumber(int x, int y, int score)const;

};