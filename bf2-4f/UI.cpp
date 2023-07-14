#include "DxLib.h"
#include "UI.h"
#include "GameMain.h"

void UI::Init() {
	gScore = 0;
}

int UI::Score() {
//	LoadDivGraph("images/Score/", 40, 8, 4, 64, 64, );
	return 0;
}

int UI::LoadImages() {
	LoadDivGraph("images/UI/UI_HiScore.png", 40, 8, 4, 64, 64, UI_image);
	return 0;
}

//void UI::DrawScore()
//{
//	//スコアの表示
//	SetFontSize(50);
//	DrawFormatString(990, 290, 0xffffff, "%d", gScore);
//	DrawString(990, 230, "Score", 0xffffff);
//}
