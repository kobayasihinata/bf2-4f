#include "DxLib.h"
#include "UI.h"
#include "GameMain.h"

 UI::UI() 
 {
	UI_image1 = LoadGraph("images/UI/UI_HiScore.png");
	UI_image2 = LoadGraph("images/UI/UI_Score.png");
	UI_image4 = LoadGraph("images/UI/UI_Stock.png");
	UI_image5 = LoadGraph("images/UI/UI_Phase.png");
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
	frame =0;

}
  
 void UI::Update()
 {
	 if (frame < 210)
	 {
		 ++frame;
	 }
 }

 void UI::Draw()const
  {
      DrawGraph(310, 7, UI_image1, TRUE);
	  DrawGraph(155, 5, UI_image2, TRUE);
	  DrawGraph(261, 25, UI_image4, TRUE);
	  DrawGraph(280, 25, UI_image4, TRUE);
	  //DrawGraph(230, 40, UI_image5, TRUE);
	  //DrawGraph(300, 20, UI_image3[0], TRUE);
	  if (frame % 50 == 0)
	  {
		  DrawGraph(230, 40, UI_image5, TRUE);
	  }
  }

 int UI::Score()
 {
	 return 0;
 }
 