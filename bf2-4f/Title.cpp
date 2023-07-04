#include "Dxlib.h"
#include "Title.h"

Title::Title()
{
	titlelogo = LoadGraph("images/Title/Title_Logo.png");
	titlecredit = LoadGraph("images/Title/Title_Credit.png");
	titlemodeselect = LoadGraph("images/Title/Title_ModeSelect.png");
	LoadDivGraph("images/Title/Title_CursorAnimation.png", 4, 4, 1, 32, 64, titlecursor);
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
	
	return this;
}

void Title::Draw()const
{
	DrawGraph(45, 10, titlelogo, TRUE);
	DrawGraph(165, 270, titlemodeselect, TRUE);
	DrawGraph(189, 430, titlecredit, TRUE);
	DrawGraph(120, 250, titlecursor[3], TRUE);
}