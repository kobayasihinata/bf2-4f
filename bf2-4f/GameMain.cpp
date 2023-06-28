#include "Dxlib.h"
#include "GameMain.h"


GameMain::GameMain()
{
	player = new Player();
	stagefloor = new StageFloor();
	staegwall = new StageWall();
}

GameMain::~GameMain()
{
	delete player;
	delete stagefloor;
	delete staegwall;
}

AbstractScene* GameMain::Update()
{
	player->HitStageCollision(stagefloor);
	player->HitStageCollision(staegwall);
	player->Update();
	return this;
}

void GameMain::Draw()const
{
	stagefloor->Draw();
	staegwall->Draw();
	player->Draw();
	DrawString(0, 0, "ƒQ[ƒ€ƒƒCƒ“", 0xff0000);
}