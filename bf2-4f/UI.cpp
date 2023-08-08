#include "DxLib.h"
#include "UI.h"
#include "GameMain.h"

  UI::UI() 
 {
	UI_image1 = LoadGraph("images/UI/UI_HiScore.png");
	UI_image2 = LoadGraph("images/UI/UI_Score.png");


	LoadDivGraph("images/UI/UI_NumAnimation.png", 10, 10, 1, 32, 32, numbers_image);
}
  
  void UI::Draw()const
  {
	  DrawGraph(170, 7, UI_image1, TRUE);
	  DrawGraph(10, 7, UI_image2, TRUE);
	  //スコア表示（仮）
	  DrawNumber(21, 0, GameMain::GetScore());

	  //ハイスコア表示(仮に現在のスコアを入れている)
	  DrawNumber(200, 0, GameMain::GetScore());
	  
  }

  void UI::DrawNumber(int x, int y, int score)const
  {
	  int a;
	  int value = score;
	  for (int i = 5; i >= 0; i--)
	  {
		  a = value % 10;
		  value /= 10;
		  //DrawFormatString(x, y + (i * 20), 0x00ff00, "%d", j);
		  DrawGraph(x + (i * 20), y, numbers_image[a], TRUE);
	  }
  }