#include <time.h>
#include "Dxlib.h"
#include "GameMain.h"
#include"GameOver.h"
#include"PadInput.h"


GameMain::GameMain()
{
	max_enemy = 3;
	player = new Player();
	for (int i = 0; i < max_enemy; i++)
	{
		enemy[i] = new Enemy(230 + i * 70, 210, 1);
		enemy_ai[i] = new ENEMY_AI;
		soapbubble[i] = new SoapBubble();
	}
	stagefloor[0] = new StageFloor(0, 416, 30, 160, 5);
	stagefloor[1] = new StageFloor(479, 416, 30, 160, 5);
	stagefloor[2] = new StageFloor(180, 260, 18, 280, 0);
	//staegwall = new StageWall();
	fish = new Fish();
	thunder = new Thunder();
	seaImage = LoadGraph("images/Stage/Stage_Sea01.png");

	Pouse = false;

	score = 0;

	for (int i = 0; i <= ENEMY_NAMBER; i++)
	{
		Avoidance[i] = FALSE;
	}
	
	damage_once = false;
}

GameMain::~GameMain()
{
	delete player;
	for (int i = 0; i < max_enemy; i++)
	{
		delete enemy[i];
		delete soapbubble[i];
	}
	//delete staegwall;
	delete stagefloor[0];
	delete stagefloor[1];
	delete stagefloor[2];
	delete thunder;
	DeleteGraph(seaImage);
}

AbstractScene* GameMain::Update()
{
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_START)) {
		Pouse = !Pouse;
	}
	if (Pouse == false) {
		thunder->Update();
		if (thunder->HitPlayer(player) == true && player->GetPlayerState() < DEATH)
		{
			player->SetThunderDeath(true);
			thunder->InitThunder();
		}
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_X))
		{
			player->SetThunderDeath(true);
		}
		//stagefloorの範囲だけループする
		for (BoxCollider* stagefloor : stagefloor)
		{
			thunder->Reflection(stagefloor);
			//プレイヤーが死亡中でないなら
			if (player->GetPlayerDeathFlg() == false && player->GetThunderDeathFlg() == false)
			{
				//各オブジェクトとの当たり判定処理
				player->HitStageCollision(stagefloor);
				//現在位置取得
				P_x = player->GetPlayerLocation().x;
				P_y = player->GetPlayerLocation().y;
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
					int E_x = enemy[i]->GetEnemyLocation().x;
					int E_y = enemy[i]->GetEnemyLocation().y;
					//敵が死亡中でない且つ死んでいないなら
					if (enemy[i]->GetEnemyDeathFlg() == false)
					{

						//各オブジェクトとの当たり判定処理
						enemy[i]->HitStageCollision(stagefloor);
						enemy_ai[i]->Update_AI_Cool();

						if (enemy[i]->No_AI_Flg() == 0)
						{
							//敵のAI取得
							switch (enemy_ai[i]->Update(P_x, P_y, E_x, E_y))
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
							default:
								break;
							}
							if (enemy_ai[i]->GetPattern() != 99) {
								enemy_ai[i]->Set_AI_Cool(enemy[i]->GetEnemyLevel() - 1);
							}
						}
						if (E_x >= P_x - 50 && E_x <= P_x + 50 && E_y >= P_y && E_y < P_y + 100)
						{
							Avoidance[i] = TRUE;
						}
						if (Avoidance[i] == TRUE) {
							enemy_ai[i]->Set_AI_Cool_Cnt(0);
							if ((E_x < P_x - 150 && E_x > P_x + 150) || (E_y < P_y - 50 || E_y >= P_y + 100)) {
								Avoidance[i] = FALSE;
							}
						}
					}

					//敵がどのオブジェクトとも着地していない場合
					if (enemy[i]->IsOnFloor(stagefloor) != true) {
						//onshare_flgをfalseにする
						enemy[i]->SetOnShareFlg(false);
					}

					//敵が死亡モーション中で無い且つプレイヤーが死亡演出中で無いなら
					if (enemy[i]->GetEnemyDeathFlg() == false && player->GetThunderDeathFlg() == false && player->GetPlayerDeathFlg() == false)
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
								Damage(i);
								break;
							case 2:
								if (enemy[i]->GetWaitFlg() == false)
								{
									player->ReflectionPX();
									enemy[i]->ReflectionMX();
								}
								Damage(i);
							case 3:
								if (enemy[i]->GetWaitFlg() == false)
								{
									player->ReflectionPY();
									enemy[i]->ReflectionMY();
								}
								Damage(i);
								break;
							case 4:
								if (enemy[i]->GetWaitFlg() == false)
								{
									enemy[i]->ReflectionPY();
									player->ReflectionMY();
								}
								Damage(i);

								break;
							default:
								damage_once = false;
								break;
							}
						}

						//敵と敵の当たり判定
						for (int j = i + 1; j < max_enemy; j++)
						{
							//敵が生きているなら
							if (enemy[j]->GetFlg() == true && enemy[i]->GetFlg() == true && enemy[i]->GetEnemyDeathFlg() == false && enemy[j]->GetEnemyDeathFlg() == false)
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
					}

					//敵が水没中なら
					if (enemy[i]->GetEnemyUnderWaterFlg() == true)
					{
						soapbubble[i]->SoapBubbleSpawn(enemy[i]->GetLocation().x);
					}
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
			if (player->GetPlayerDeathFlg() == false)
			{
				score += soapbubble[i]->HitPlayerCollision(player);
			}

		}

		player->Update();
		fish->Update();

		//プレイヤーが死んでいる場合海に戻る
		if (player->GetIsDie() == true)
		{
			fish->NotAtSeaSurface();
		}

		//海面にプレイヤーがいる場合
		if (fish->CheckSeaSurface(player) == true)
		{
			//捕食処理：ターゲットはプレイヤー
			fish->TargetPrey(player);
			//プレイヤーが捕食された場合
			//画像を非表示にして死んでいる判定にする
			if (fish->GetIsPreyedOnPlayer() == true)
			{
				player->SetShowFlg(false);
				player->SetIsDie(true);
			}
		}
		else
		{
			for (int i = 0; i < max_enemy; i++)
			{
				if (enemy[i]->GetIsDie() == true)
				{
					fish->NotAtSeaSurface();
				}

				//海面に敵のいずれかがいる場合
				if (fish->CheckSeaSurface(enemy[i]) == true)
				{
					//敵のレベルを取得する
					fish->SetSaveEnemyLevel(enemy[i]->GetEnemyLevel());

					//捕食処理：ターゲットは敵
					fish->TargetPrey(enemy[i]);

					//敵が捕食された場合
					//画像を非表示にしてenemyのflgをfalseにする
					if (fish->GetIsPreyedOnEnemyr() == true)
					{
						enemy[i]->SetEnemyUnderWaterFlg(false);
						enemy[i]->SetShowFlg(false);
						enemy[i]->SetFlg(false);
						enemy[i]->SetIsDie(true);
					}
					//念のため死んでいる判定にする
					if (enemy[i]->GetShowFlg() == false)	
					{
						enemy[i]->SetIsDie(true);
						enemy[i]->SetFlg(false);
					}
				}
			}

		}

		//プレイヤーか敵のいずれも海面にいない場合海に戻る
		if (fish->CheckSeaSurface(player) == false &&
			fish->CheckSeaSurface(enemy[0]) == false &&
			fish->CheckSeaSurface(enemy[1]) == false &&
			fish->CheckSeaSurface(enemy[2]) == false)
		{
			fish->NotAtSeaSurface();
		}

		//さかな側でプレイヤーのスポーンフラグがたったら
		if (fish->GetRespawnFlg() == true)
		{
			player->SetShowFlg(true);
			player->SetPlayerLife(-1);
			player->SetIsDie(false);
			player->PlayerRespawn(PLAYER_RESPAWN_POS_X, PLAYER_RESPAWN_POS_Y);
			fish->SetRespawnFlg(false);
		}

		//プレイヤーの残機が0より小さい場合タイトルに戻る
		if (player->GetPlayerLife() < 0) 
		{
			return new GameOver();
		}
	}
	return this;
}

void GameMain::Draw()const
{
	
	stagefloor[0]->DrawLandLeft();
	stagefloor[1]->DrawLandRight();
	stagefloor[2]->DrawFooting1();
	thunder->Draw(Pouse);
	//デバッグ用　当たり判定表示
	for (BoxCollider* stagefloor : stagefloor)
	{
		stagefloor->Draw();
	}
	if (Pouse == false) {
		player->Draw();

	}
	if (Pouse == false) {
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

void GameMain::Damage(int i)
{
	//プレイヤーの25上の座標に敵がいるならプレイヤーの風船を減らす
	if (enemy[i]->GetLocation().y + BALLOON_HEIGHT < player->GetLocation().y && enemy[i]->GetEnemyParaFlg() == false && damage_once == false)
	{
		player->BalloonDec();
		damage_once = true;
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
