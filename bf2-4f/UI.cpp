#include "DxLib.h"
#include "UI.h"
#include "GameMain.h"

UI::UI() 
{
	UI_image1 = LoadGraph("images/UI/UI_HiScore.png");
	UI_image2 = LoadGraph("images/UI/UI_Score.png");

	ReadHighScore();

	LoadDivGraph("images/UI/UI_NumAnimation.png", 10, 10, 1, 32, 32, numbers_image);
}

UI::~UI()
{
	DeleteGraph(UI_image1);
	DeleteGraph(UI_image2);
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(numbers_image[i]);
	}
	if (GameMain::GetScore() > high_score)
	{
		SaveHighScore();
	}
}
void UI::Draw()const
{
	DrawGraph(170, 7, UI_image1, TRUE);
	DrawGraph(10, 7, UI_image2, TRUE);

	//スコア表示（仮）
	DrawNumber(21, 0, GameMain::GetScore());

	//ハイスコア表示(仮に現在のスコアを入れている)
	if (GameMain::GetScore() > high_score)
	{
		DrawNumber(200, 0, GameMain::GetScore());
	}
	else
	{
		DrawNumber(200, 0, high_score);
	}
  
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

void UI::ReadHighScore()
{
	FILE* fp;
#pragma warning(disable:4996)
	//ファイルオープン
	fp = fopen("dat/HighScore.txt", "r");
	fscanf(fp, "%6d", &high_score);
	//ファイルクローズ
	fclose(fp);
}

void UI::SaveHighScore()
{
	FILE* fp;
#pragma warning(disable:4996)
	//ファイルオープン
	fp = fopen("dat/HighScore.txt", "w");
	fprintf(fp, "%6d", GameMain::GetScore());
	//ファイルクローズ
	fclose(fp);
}