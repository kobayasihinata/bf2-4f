#include "Dxlib.h"
#include "GameMain.h"


GameMain::GameMain()
{
	player = new Player();
	stagefloor = new StageFloor();
}

GameMain::~GameMain()
{
	delete player;
	delete stagefloor;
}

AbstractScene* GameMain::Update()
{
	player->SetOnFloor(false);
	player->Update();
	player->SetCollisionLocation(stagefloor);

	return this;
}

void GameMain::Draw()const
{
	stagefloor->Draw();
	player->Draw();
	DrawString(0, 0, "ƒQ[ƒ€ƒƒCƒ“", 0xff0000);
}