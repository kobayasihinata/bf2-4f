#include "Dxlib.h"
#include "GameMain.h"
#include"Title.h"
#include"PadInput.h"


GameMain::GameMain()
{
	max_enemy = 3;
	player = new Player();
	for (int i = 0; i < max_enemy; i++)
	{
		enemy[i] = new Enemy(220+i*80, 210, 1);
		enemy_ai[i] = new ENEMY_AI;
		soapbubble[i] = new SoapBubble();
	}
	stagefloor[0] = new StageFloor(0, 416, 30, 160, 5);
	stagefloor[1] = new StageFloor(479, 416, 30, 160, 5);
	stagefloor[2] = new StageFloor(180, 260, 18, 280, 0);
	staegwall = new StageWall();
	fish = new Fish();
	seaImage = LoadGraph("images/Stage/Stage_Sea01.png");

	Pouse = false;

	score = 0;
	move_cooltime = Enemy_Move_Cool[1];
}

GameMain::~GameMain()
{
	delete player;
	for (int i = 0; i < max_enemy; i++)
	{
		delete enemy[i];
		delete soapbubble[i];
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

			for (int i = 0; i < max_enemy; i++)
			{
				if (enemy[i]->GetFlg() == true)
				{
					//敵が死亡中でないなら
					if (enemy[i]->GetEnemyDeathFlg() == false)
					{

						//各オブジェクトとの当たり判定処理
						enemy[i]->HitStageCollision(stagefloor);
						//敵のAI取得

						if (++move_cooltime >= Enemy_Move_Cool[enemy[i]->GetEnemyLevel() - 1] && enemy[i]->No_AI_Flg() == 0)
						{
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
								enemy[i]->SetNot_AI(300);
								if (enemy[i]->GetEnemyLocation().y + 10 > player->GetPlayerLocation().y) {
									enemy[i]->EnemyJumpStop();
								}
								break;
							default:
								break;
							}
						}
					}
				}


				//敵がどのオブジェクトとも着地していない場合
				if (enemy[i]->IsOnFloor(stagefloor) != true) {
					//onshare_flgをfalseにする
					enemy[i]->SetOnShareFlg(false);
				}

				//敵が死亡モーション中で無ければ
				if (enemy[i]->GetEnemyDeathFlg() == false)
				{
					//プレイヤーが無敵状態でないなら
					if (player->GetPlayerRespawn() <= 0)
					{
						//プレイヤーと敵の当たり判定
						switch (player->HitEnemyCollision(enemy[i]))
						{
						case 1:
							if (enemy[i]->GetWaitFlg() == false)
							{
								player->ReflectionMX();
								enemy[i]->ReflectionPX();
							}
							Damege(i);
							break;
						case 2:
							if (enemy[i]->GetWaitFlg() == false)
							{
								player->ReflectionPX();
								enemy[i]->ReflectionMX();
							}
							Damege(i);
							break;
						case 3:
							if (enemy[i]->GetWaitFlg() == false)
							{
								player->ReflectionPY();
								enemy[i]->ReflectionMY();
							}
							Damege(i);
							break;
						case 4:
							if (enemy[i]->GetWaitFlg() == false)
							{
								enemy[i]->ReflectionPY();
								player->ReflectionMY();
							}
							Damege(i);
							break;
						default:
							break;
						}
					}

					//敵と敵の当たり判定
					for (int j = i + 1; j < max_enemy; j++)
					{
						switch (enemy[j]->HitEnemyCollision(enemy[i]))
						{
						case 1:
							enemy[j]->ReflectionMX();
							enemy[i]->ReflectionPX();
							break;
						case 2:
							enemy[j]->ReflectionPX();
							enemy[i]->ReflectionMX();
							break;
						case 3:
							enemy[j]->ReflectionPY();
							enemy[i]->ReflectionMY();
							break;
						case 4:
							enemy[j]->ReflectionMY();
							enemy[i]->ReflectionPY();
							break;
						default:
							break;
						}
					}
				}

				//敵が水没中なら
				if (enemy[i]->GetEnemyUnderWaterFlg() == true)
				{
					soapbubble[i]->SoapBubbleSpawn(enemy[i]->GetLocation().x);
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
		for (int i = 0; i < max_enemy; i++)
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
			soapbubble[i]->Update();
			score += soapbubble[i]->HitPlayerCollision(player);
		}

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
						enemy[i]->SetFlg(false);
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

		return this;
	}
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
		for (int i = 0; i < max_enemy; i++)
		{
			enemy[i]->Draw();
			soapbubble[i]->Draw();
		}
	}
	fish->Draw();
	DrawGraph(159, 444, seaImage, TRUE);

	//スコア表示（仮）
	DrawNumber(0, 0, score);
}

void GameMain::Damege(int i)
{
	//プレイヤーの25上の座標に敵がいるならプレイヤーの風船を減らす
	if (enemy[i]->GetLocation().y + BALLOON_HEIGHT < player->GetLocation().y)
	{
		player->BalloonDec();
	}

	//プレイヤーの25下の座標に敵がいるならプレイヤーの風船を減らす
	if (enemy[i]->GetLocation().y > player->GetLocation().y + BALLOON_HEIGHT)
	{
		score += enemy[i]->ApplyDamege();
	}

	//敵が風船を膨らませる前なら胴体に接触してもダメージが入る
	if (enemy[i]->GetWaitFlg() == true)
	{
		score += enemy[i]->ApplyDamege();
	}
}
