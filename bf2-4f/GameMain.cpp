#include "Dxlib.h"
#include "GameMain.h"


GameMain::GameMain()
{
	player = new Player();
	stagefloor = new StageFloor();
	collisionFlg = false;
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
	DrawString(0, 0, "ƒQ[ƒ€ƒƒCƒ“", 0xff0000);
}