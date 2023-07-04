#include "Dxlib.h"
#include "Title.h"

Title::Title()
{
	titlelogo = LoadGraph("images/Title/Title_Logo.png");
	titlecredit = LoadGraph("images/Title/Title_Credit.png");
	titlemodeselect = LoadGraph("images/Title/Title_ModeSelect.png");
}

Title::~Title()
{
	DeleteGraph(titlelogo);
	DeleteGraph(titlecredit);
	DeleteGraph(titlemodeselect);
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
}