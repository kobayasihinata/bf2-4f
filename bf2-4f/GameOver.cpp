#include "DxLib.h"
#include "PadInput.h"
#include "GameOver.h"
#include "Title.h"

GameOver::GameOver() {
	//if (GameOver_Img == 0) {
		GameOver_Img = LoadGraph("images/UI/UI_GameOver.png");
	//}
	WaitTimer = SECOND_TO_FRAME(4);
}
GameOver::~GameOver() {
	
}
AbstractScene* GameOver::Update() {
	PAD_INPUT::UpdateKey();
	if (--WaitTimer <= 0 || PAD_INPUT::OnButton(XINPUT_BUTTON_START)) {
		return new Title();
	}
	return this;
}
void GameOver::Draw()const {
	DrawGraph(221, 233, GameOver_Img, 0);
}