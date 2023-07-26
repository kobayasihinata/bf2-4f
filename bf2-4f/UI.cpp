#include "DxLib.h"
#include "UI.h"
#include "GameMain.h"

  UI::UI() 
 {
	UI_image1 = LoadGraph("images/UI/UI_HiScore.png");
	UI_image2 = LoadGraph("images/UI/UI_Score.png");
	for (int i = 0; i < 10; i++)
	{
		UI_image3[i] = NULL;
	}
	LoadDivGraph("images/UI/UI_NumAnimation.png", 10, 10, 1, 32, 32, UI_image3);
	Score_image = LoadGraph("images/Score/GetScore_500.png");
	Score_image = LoadGraph("images/Score/GetScore_750.png");
	Score_image = LoadGraph("images/Score/GetScore_1000.png");
	Score_image = LoadGraph("images/Score/GetScore_1500.png");
	Score_image = LoadGraph("images/Score/GetScore_2000.png");
}
  
  void UI::Draw()const
  {
	  DrawGraph(300, 5, UI_image1, TRUE);
	  DrawGraph(170, 5, UI_image2, TRUE);
	  DrawGraph(190, 0, UI_image3[0], TRUE);

	  
  }

 int UI::Score()
 {
	 return 0;
 }