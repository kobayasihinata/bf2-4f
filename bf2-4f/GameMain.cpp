#include "Dxlib.h"
#include "GameMain.h"
#include"Title.h"
#include"PadInput.h"


GameMain::GameMain()
{
	player = new Player();
	stagefloor = new StageFloor();
	staegwall = new StageWall();
	Pouse = false;
}

GameMain::~GameMain()
{
	delete player;
	delete stagefloor;
	delete staegwall;
}

AbstractScene* GameMain::Update()
{
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_START)) {
		Pouse = !Pouse;
	}

	if (Pouse==false) {
		player->HitStageCollision(staegwall);
		player->HitStageCollision(stagefloor);
		player->Update();
		if (player->GetPlayerLife() < 0) {
			return new Title();
		}
	}
	
	

	
	return this;
}

void GameMain::Draw()const
{
	stagefloor->Draw();
	staegwall->Draw();
	if (Pouse == false) {
		player->Draw();
	}
	DrawString(0, 0, "ƒQ[ƒ€ƒƒCƒ“", 0xff0000);
}