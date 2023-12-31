#include "DxLib.h"
#include "UI.h"
#include "GameMain.h"

UI::UI() 
{
	highscore_image = LoadGraph("images/UI/UI_HiScore.png");
	score_image = LoadGraph("images/UI/UI_Score.png");
	player_life_image = LoadGraph("images/UI/UI_Stock.png");
	high_score = 0;
	ReadHighScore();

	LoadDivGraph("images/UI/UI_NumAnimation.png", 10, 10, 1, 32, 32, numbers_image);
}

UI::~UI()
{
	DeleteGraph(highscore_image);
	DeleteGraph(score_image);
	DeleteGraph(player_life_image);
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(numbers_image[i]);
	}
}
void UI::Draw(int life)const
{
	DrawGraph(170, 7, highscore_image, TRUE);
	DrawGraph(10, 7, score_image, TRUE);

	//スコア表示（仮）
	DrawNumber(21, 0, GameMain::GetScore(),6);

	//ハイスコア表示
	if (GameMain::GetScore() > high_score)
	{
		DrawNumber(200, 0, GameMain::GetScore(),6);
	}
	else
	{
		DrawNumber(200, 0, high_score,6);
	}
  
	//プレイヤー残機表示
	for (int i = 0; i < life; i++)
	{
		DrawGraph(110-(i*17), 25, player_life_image, TRUE);
	}
}

void UI::DrawNumber(int x, int y, int score, int wordcount)const
 {
	 int a;
	int value = score;

	for (int i = wordcount-1; i >= 0; i--)
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