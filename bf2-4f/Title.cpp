#include "Dxlib.h"
#include "Title.h"
#include "GameMain.h"
#include "PadInput.h"

Title::Title()
{
	titlelogo = LoadGraph("images/Title/Title_Logo.png");
	titlecredit = LoadGraph("images/Title/Title_Credit.png");
	titlemodeselect = LoadGraph("images/Title/Title_ModeSelect.png");
	interval = 75;
	select = 0;
}

Title::~Title()
{
	DeleteGraph(titlelogo);
	DeleteGraph(titlecredit);
	DeleteGraph(titlemodeselect);
}

AbstractScene* Title::Update()
{
	GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (interval < 75)interval++;
	JoyPadY = PAD_INPUT::GetLStick().ThumbY;

	if (JoyPadY > MARGIN && interval >= 75) {
		select--;
		interval = 0;
	}
	else if (JoyPadY < -MARGIN && interval >= 75) {
		select++;
		interval = 0;
	}

	if (select < 0)select = 2;
	if (select > 2)select = 0;

	if (PAD_INPUT::OnButton(XINPUT_BUTTON_START)) {

		//äeÉVÅ[Éì
		if (select == 0) return new GameMain();
		//if (select == 1) return new Ranking();
		//if (select == 2) return new End();

	}

	return this;
}

void Title::Draw()const
{
	DrawGraph(45, 10, titlelogo, TRUE);
	DrawGraph(165, 270, titlemodeselect, TRUE);
	DrawGraph(189, 430, titlecredit, TRUE);
	DrawFormatString(100, 300, 0xffffff, "%d", select);
}