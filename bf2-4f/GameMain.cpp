#include "Dxlib.h"
#include "GameMain.h"

GameMain::GameMain()
{

}

GameMain::~GameMain()
{

}

AbstractScene* GameMain::Update()
{

	return this;
}

void GameMain::Draw()const
{
	DrawString(0, 0, "ƒQ[ƒ€ƒƒCƒ“", 0xff0000);
}