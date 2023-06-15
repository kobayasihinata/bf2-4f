#include "Dxlib.h"
#include "GameMain.h"

GameMain::GameMain()
{
	player = new Player();
}

GameMain::~GameMain()
{
	delete player;
}

AbstractScene* GameMain::Update()
{
	player->Update();
	return this;
}

void GameMain::Draw()const
{
	player->Draw();
	DrawString(0, 0, "ゲームメイン", 0xff0000);
}