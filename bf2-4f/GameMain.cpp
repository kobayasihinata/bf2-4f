#include "Dxlib.h"
#include "GameMain.h"
#include "UI.h"
UI ui;

GameMain::GameMain()
{
	player = new Player();
	stagefloor = new StageFloor();
	collisionFlg = false;
	ui.Init();
}

GameMain::~GameMain()
{
	delete player;
	delete stagefloor;
}

AbstractScene* GameMain::Update()
{
	player->Update();
	if (stagefloor->HitCheck(player)) {
		collisionFlg = true;
	}
	else {
		collisionFlg = false;
	}
	return this;
}

void GameMain::Draw()const
{
	stagefloor->Draw();
	player->Draw();
	if (collisionFlg == true) {
		DrawString(player->GetLocation().x, player->GetLocation().y, "Hit", 0xffffff, 0x000000);
	}
	DrawString(0, 0, "ゲームメイン", 0xff0000);
	DrawFormatString(200, 10, GetColor(255, 255, 255), "I:%d");
	DrawFormatString(250, 10, GetColor(255, 255, 255), "TOP:%d");
}