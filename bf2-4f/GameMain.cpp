#include "Dxlib.h"
#include "GameMain.h"
#include"Title.h"
#include"PadInput.h"


GameMain::GameMain()
{
	player = new Player();
	enemy = new Enemy(300,210,1);
	stagefloor[0] = new StageFloor(0, 416, 30, 160, 5);
	stagefloor[1] = new StageFloor(479, 416, 30, 160, 5);
	stagefloor[2] = new StageFloor(180, 260, 18, 280, 0);
	staegwall = new StageWall();
	fish = new Fish();
	seaImage = LoadGraph("images/Stage/Stage_Sea01.png");

	Pouse = false;
}

GameMain::~GameMain()
{
	delete player;
	delete enemy;
	delete staegwall;
	delete stagefloor[0];
	delete stagefloor[1];
	delete stagefloor[2];
	DeleteGraph(seaImage);
}

AbstractScene* GameMain::Update()
{
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_START)) {
		Pouse = !Pouse;
	}
	if (Pouse == false) {
		//stagefloorの範囲だけループする
		for (BoxCollider* stagefloor : stagefloor)
		{
			//プレイヤーが死亡中でないなら
			if (player->GetPlayerDeathFlg() == false)
			{
				//各オブジェクトとの当たり判定処理
				player->HitStageCollision(stagefloor);
			}

			//各オブジェクトとの当たり判定処理
			enemy->HitStageCollision(stagefloor);
		
			//プレイヤーがどのオブジェクトとも着地していない場合
			if (player->IsOnFloor(stagefloor) != true) {
				//onshare_flgをfalseにする
				player->SetOnShareFlg(false);
			}

			//敵がどのオブジェクトとも着地していない場合
			if (enemy->IsOnFloor(stagefloor) != true) {
				//onshare_flgをfalseにする
				enemy->SetOnShareFlg(false);
			}
		}
		//プレイヤーが各オブジェクトのいずれかに着地している場合
		if (player->IsOnFloor(stagefloor[0]) == true ||
			player->IsOnFloor(stagefloor[1]) == true ||
			player->IsOnFloor(stagefloor[2]) == true)
		{
			//onshare_flgをtrueにする
			player->SetOnShareFlg(true);
		}
		//敵が各オブジェクトのいずれかに着地している場合
		if (enemy->IsOnFloor(stagefloor[0]) == true ||
			enemy->IsOnFloor(stagefloor[1]) == true ||
			enemy->IsOnFloor(stagefloor[2]) == true)
		{
			//onshare_flgをtrueにする
			enemy->SetOnShareFlg(true);
		}
		player->Update();
		enemy->Update();
		enemy->EnemyMoveLeft();
		enemy->EnemyJump();
		fish->SetSaveEnemyLevel(enemy->GetEnemyLevel());
		fish->Update(player);
		if (fish->GetIsPreyedOnPlayer() == true)
		{
     		player->SetShowFlg(false);
		}	
		if (fish->GetRespawnFlg() == true)
		{
			player->SetShowFlg(true);
   			player->SetPlayerLife(-1);
			player->PlayerRespawn(300, 350);
			fish->SetRespawnFlg(false);
		}

		//プレイヤーの残機が0より小さい場合タイトルに戻る
		if (player->GetPlayerLife() < 0) {
			return new Title();
		}
	}
	return this;
}

void GameMain::Draw()const
{
	if (Pouse == false) {
		player->Draw();
		enemy->Draw();
	}
	stagefloor[0]->DrawLandLeft();
	stagefloor[1]->DrawLandRight();
	stagefloor[2]->DrawFooting1();
	//デバッグ用　当たり判定表示
	for (BoxCollider* stagefloor : stagefloor)
	{
		stagefloor->Draw();
	}
	DrawString(0, 0, "ゲームメイン", 0xff0000);
	
	DrawGraph(159, 444, seaImage, TRUE);
	fish->Draw();
}