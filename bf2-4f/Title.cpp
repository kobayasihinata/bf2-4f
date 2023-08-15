#include "Dxlib.h"
#include "Title.h"
#include"PadInput.h"
#include"GameMain.h"


Title::Title()
{
	titlelogo = LoadGraph("images/Title/Title_Logo.png");
	titlecredit = LoadGraph("images/Title/Title_Credit.png");
	titlemodeselect = LoadGraph("images/Title/Title_ModeSelect.png");
	LoadDivGraph("images/Title/Title_CursorAnimation.png", 4, 4, 1, 32, 64, titlecursor);
	cursor_num = 0;
	cursor_y = 0;
	interval = 0;
}

Title::~Title()
{
	DeleteGraph(titlelogo);
	DeleteGraph(titlecredit);
	DeleteGraph(titlemodeselect);
	DeleteGraph(titlecursor[3]);
}

AbstractScene* Title::Update()
{
	cursor_y = cursor_num * 35;
	if (interval < 30) {
		interval++;
	}

	if ((PAD_INPUT::GetLStick().ThumbY > MARGIN || CheckHitKey(KEY_INPUT_W)) && interval >= 30) {
		cursor_num--;
		interval = 0;
	}
	else if ((PAD_INPUT::GetLStick().ThumbY < -MARGIN || CheckHitKey(KEY_INPUT_S)) && interval >= 30) {
		cursor_num++;
		interval = 0;
	}

	if (cursor_num < 0)cursor_num = 2;
	if (cursor_num > 2)cursor_num = 0;

	if (cursor_num == 0 && PAD_INPUT::OnButton(XINPUT_BUTTON_START) || CheckHitKey(KEY_INPUT_SPACE))
	{
		return new GameMain(0);
	}

	return this;
}

void Title::Draw()const
{
	DrawGraph(45, 10, titlelogo, TRUE);
	DrawGraph(TITLEMODESELECT_X, TITLEMODESELECT_Y, titlemodeselect, TRUE);
	DrawGraph(189, 430, titlecredit, TRUE);
	DrawGraph(TITLEMODESELECT_X - 50, TITLEMODESELECT_Y - 20 + cursor_y, titlecursor[1], TRUE);
}