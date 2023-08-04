#include "DxLib.h"
#include "PadInput.h"
#include "GameOver.h"
#include "Title.h"

GameOver::GameOver() {
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
	DrawFormatString(300, 300, 0xffffff, "GameOver");
}