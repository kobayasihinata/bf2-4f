#include "Dxlib.h"
#include "GameMain.h"
#include"Title.h"
#include"PadInput.h"


GameMain::GameMain()
{
	player = new Player();
	for (int i = 0; i < 3; i++)
	{
		enemy[i] = new Enemy(220+i*80, 210, i+1);
		enemy_ai[i] = new ENEMY_AI;
	}
	stagefloor[0] = new StageFloor(0, 416, 30, 160, 5);
	stagefloor[1] = new StageFloor(479, 416, 30, 160, 5);
	stagefloor[2] = new StageFloor(180, 260, 18, 280, 0);
	staegwall = new StageWall();
	fish = new Fish();
	seaImage = LoadGraph("images/Stage/Stage_Sea01.png");

	Pouse = false;

	px, py, ex, ey = 0;
	score = 0;
}

GameMain::~GameMain()
{
	delete player;
	for (int i = 0; i < 3; i++)
	{
		delete enemy[i];
	}
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

			//プレイヤーがどのオブジェクトとも着地していない場合
			if (player->IsOnFloor(stagefloor) != true) {
				//onshare_flgをfalseにする
				player->SetOnShareFlg(false);
			}

			for (int i = 0; i < 3; i++)
			{
				//敵が死亡中でないなら
				if (enemy[i]->GetEnemyDeathFlg() == false)
				{
					//各オブジェクトとの当たり判定処理
					enemy[i]->HitStageCollision(stagefloor);
					//敵のAI取得
					switch (enemy_ai[i]->Update(player->GetPlayerLocation().x, player->GetPlayerLocation().y,
						enemy[i]->GetEnemyLocation().x, enemy[i]->GetEnemyLocation().y))
					{
					case 0:
						enemy[i]->EnemyMoveLeft();
						enemy[i]->EnemyJump();
						break;
					case 1:
						enemy[i]->EnemyMoveRight();
						enemy[i]->EnemyJump();
						break;
					case 2:
						enemy[i]->EnemyMoveLeft();
						enemy[i]->EnemyJumpStop();
						break;
					case 3:
						enemy[i]->EnemyMoveRight();
						enemy[i]->EnemyJumpStop();
						break;
					case 4:
						break;
					default:
						break;
					}
				}

				//敵がどのオブジェクトとも着地していない場合
				if (enemy[i]->IsOnFloor(stagefloor) != true) {
					//onshare_flgをfalseにする
					enemy[i]->SetOnShareFlg(false);
				}
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
		//敵の数だけ繰り返す
		for (int i = 0; i < 3; i++)
		{
			//敵が各オブジェクトのいずれかに着地している場合
			if (enemy[i]->IsOnFloor(stagefloor[0]) == true ||
				enemy[i]->IsOnFloor(stagefloor[1]) == true ||
				enemy[i]->IsOnFloor(stagefloor[2]) == true)
			{
				//onshare_flgをtrueにする
				enemy[i]->SetOnShareFlg(true);
			}
			enemy[i]->Update();

		}

		//実験用ダメージ処理
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_LEFT_SHOULDER))score += enemy[0]->ApplyDamege();
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_RIGHT_SHOULDER))score += enemy[1]->ApplyDamege();
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_LEFT_THUMB))score += enemy[2]->ApplyDamege();

		player->Update();
		fish->Update();
		if (player->GetIsDie() == true)
		{
			fish->NotAtSeaSurface();
		}

		if (fish->CheckSeaSurface(player) == true)
		{
			fish->TargetPrey(player);
			if (fish->GetIsPreyedOnPlayer() == true)
			{
				player->SetShowFlg(false);
				player->SetIsDie(true);
			}
		}
		else
		{
			for (int i = 0; i < 3; i++)
			{
				if (fish->CheckSeaSurface(enemy[i]) == true)
				{
					fish->SetSaveEnemyLevel(enemy[i]->GetEnemyLevel());

					fish->TargetPrey(enemy[i]);

					if (fish->GetIsPreyedOnEnemyr() == true)
					{
						enemy[i]->SetShowFlg(false);
					}
					if (enemy[i]->GetShowFlg() == false)	//念のため
					{
						enemy[i]->SetIsDie(true);
					}
				}
			}

		}

		if (fish->CheckSeaSurface(player) == false &&
			fish->CheckSeaSurface(enemy[0]) == false &&
			fish->CheckSeaSurface(enemy[1]) == false &&
			fish->CheckSeaSurface(enemy[2]) == false)
		{
			fish->NotAtSeaSurface();
		}

		if (fish->GetRespawnFlg() == true)
		{
			player->SetShowFlg(true);
   			player->SetPlayerLife(-1);
			player->SetIsDie(false);
			player->PlayerRespawn(PLAYER_RESPAWN_POS_X, PLAYER_RESPAWN_POS_Y);
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
	stagefloor[0]->DrawLandLeft();
	stagefloor[1]->DrawLandRight();
	stagefloor[2]->DrawFooting1();
	//デバッグ用　当たり判定表示
	for (BoxCollider* stagefloor : stagefloor)
	{
		stagefloor->Draw();
	}
	if (Pouse == false) {
		player->Draw();
		for (int i = 0; i < 3; i++)
		{
			enemy[i]->Draw();
		}
	}
	fish->Draw();
	DrawGraph(159, 444, seaImage, TRUE);

	//スコア表示（仮）
	DrawFormatString(600, 0, 0x00ffff, "%d",score);
	DrawString(0, 0, "LBボタン：敵１にダメージ", 0xff0000);
	DrawString(0, 20, "RBボタン：敵２にダメージ", 0xff0000);
	DrawString(0, 40, "左スティック押し込み：敵３にダメージ", 0xff0000);
	DrawString(0, 60, "右スティック押し込み：プレイヤーにダメージ", 0xff0000);
}
