#include <time.h>
#include "Dxlib.h"
#include "GameMain.h"
#include"GameOver.h"
#include"PadInput.h"

static int score;      //現在のステージ数

GameMain::GameMain()
{
	stage = 0;
	player = new Player();
	for (int i = 0; i < MAX_FLOOR; i++)
	{
		stagefloor[i] = new StageFloor(0, 0, 0, 0, 0);
	}
	for (int i = 0; i < MAX_WALL; i++)
	{
		stagewall[i] = new StageWall(0, 0, 0, 0, 0);
	}
	CreateStage(stage);
	//staegwall = new StageWall();
	fish = new Fish();
	ui = new UI();
	seaImage = LoadGraph("images/Stage/Stage_Sea01.png");
	GameStart_BGM = LoadSoundMem("sounds/SE_Start.wav");
	EnemuyMove_SE = LoadSoundMem("sounds/SE_EnemyMove.wav");
	PlaySoundMem(GameStart_BGM, DX_PLAYTYPE_BACK);

	Pouse = false;

	score = 0;

	for (int i = 0; i <= ENEMY_NAMBER; i++)
	{
		Avoidance[i] = FALSE;
	}
	
	damage_once = false;
	clear_flg = false;
	clear_wait = 0;
}

GameMain::~GameMain()
{
	delete player;
	for (int i = 0; i < max_enemy; i++)
	{
		delete enemy[i];
		delete soapbubble[i];
	}
	
	for (int i = 0; i < MAX_FLOOR; i++)
	{
		delete stagefloor[i];
	}
	for (int i = 0; i < MAX_WALL; i++)
	{
		delete stagewall[i];
	}
	delete thunder;
	delete ui;
	DeleteGraph(seaImage);
	score = 0;
}

AbstractScene* GameMain::Update()
{
	//敵全撃破後の演出中で無ければ
	if (clear_wait <= 0)
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
			//現在のstagefloorの数だけループする
			for (int i = 0; i < now_floor_max; i++)
			{
				thunder->Reflection(stagefloor[i]);
				//プレイヤーが死亡中でないなら
				if (player->GetPlayerDeathFlg() == false && player->GetThunderDeathFlg() == false)
				{
					//各オブジェクトとの当たり判定処理
					player->HitStageCollision(stagefloor[i]);
					//現在位置取得
					P_x = player->GetPlayerLocation().x;
					P_y = player->GetPlayerLocation().y;
				}

				//プレイヤーがいずれかのオブジェクトに着地していない場合
				if (player->IsOnFloor(stagefloor[i]) != true)
				{
					//onshare_flgをfalseにする
					player->SetOnShareFlg(false);
				}

				for (int j = 0; j < max_enemy; j++)
				{
					if (enemy[j]->GetFlg() == true)
					{
						int E_x = enemy[j]->GetEnemyLocation().x;
						int E_y = enemy[j]->GetEnemyLocation().y;
						//敵が死亡中でない且つ死んでいないなら
						if (enemy[j]->GetEnemyDeathFlg() == false)
						{

							//各オブジェクトとの当たり判定処理
							enemy[j]->HitStageCollision(stagefloor[i]);
							enemy_ai[j]->Update_AI_Cool();

							if (enemy[j]->No_AI_Flg() == 0)
							{
								//敵のAI取得
								switch (enemy_ai[j]->Update(P_x, P_y, E_x, E_y))
								{
								case 0:
									enemy[j]->EnemyMoveLeft();
									enemy[j]->EnemyJump();
									break;
								case 1:
									enemy[j]->EnemyMoveRight();
									enemy[j]->EnemyJump();
									break;
								case 2:
									enemy[j]->EnemyMoveLeft();
									enemy[j]->EnemyJumpStop();
									break;
								case 3:
									enemy[j]->EnemyMoveRight();
									enemy[j]->EnemyJumpStop();
									break;
								default:
									break;
								}
								if (enemy_ai[j]->GetPattern() != 99) {
									enemy_ai[j]->Set_AI_Cool(enemy[j]->GetEnemyLevel() - 1);
								}
							}
							if (E_x >= P_x - 50 && E_x <= P_x + 50 && E_y >= P_y && E_y < P_y + 100)
							{
								Avoidance[j] = TRUE;
							}
							if (Avoidance[j] == TRUE) {
								enemy_ai[j]->Set_AI_Cool_Cnt(0);
								if ((E_x < P_x - 150 && E_x > P_x + 150) || (E_y < P_y - 50 || E_y >= P_y + 100)) {
									Avoidance[j] = FALSE;
								}
							}
						}

						//敵がいずれかのオブジェクトに着地していない場合
						if (enemy[j]->IsOnFloor(stagefloor[j]) != true)
						{
							//onshare_flgをfalseにする
							enemy[j]->SetOnShareFlg(false);
						}

						//敵が死亡モーション中で無い且つプレイヤーが死亡演出中で無いなら
						if (enemy[j]->GetEnemyDeathFlg() == false && player->GetThunderDeathFlg() == false && player->GetPlayerDeathFlg() == false)
						{
							//プレイヤーが無敵状態でないなら
							if (player->GetPlayerRespawn() <= 0)
							{
								//プレイヤーと敵の当たり判定
								switch (player->HitEnemyCollision(enemy[j]))
								{
								case 1:
									if (enemy[j]->GetWaitFlg() == false)
									{
										player->ReflectionMX();
										enemy[j]->ReflectionPX();
									}
									Damage(j);
									break;
								case 2:
									if (enemy[j]->GetWaitFlg() == false)
									{
										player->ReflectionPX();
										enemy[j]->ReflectionMX();
									}
									Damage(j);
								case 3:
									if (enemy[j]->GetWaitFlg() == false)
									{
										player->ReflectionPY();
										enemy[j]->ReflectionMY();
									}
									Damage(j);
									break;
								case 4:
									if (enemy[j]->GetWaitFlg() == false)
									{
										enemy[j]->ReflectionPY();
										player->ReflectionMY();
									}
									Damage(j);

									break;
								default:
									damage_once = false;
									break;
								}
							}

							//敵と敵の当たり判定
							for (int k = j + 1; k < max_enemy; k++)
							{
								//敵が生きているなら
								if (enemy[k]->GetFlg() == true && enemy[j]->GetFlg() == true && enemy[j]->GetEnemyDeathFlg() == false && enemy[k]->GetEnemyDeathFlg() == false)
								{
									switch (enemy[k]->HitEnemyCollision(enemy[j]))
									{
									case 1:
										enemy[k]->ReflectionMX();
										enemy[j]->ReflectionPX();
										break;
									case 2:
										enemy[k]->ReflectionPX();
										enemy[j]->ReflectionMX();
										break;
									case 3:
										enemy[k]->ReflectionPY();
										enemy[j]->ReflectionMY();
										break;
									case 4:
										enemy[k]->ReflectionMY();
										enemy[j]->ReflectionPY();
										break;
									default:
										break;
									}
								}
							}
						}

						//敵が水没中なら
						if (enemy[j]->GetEnemyUnderWaterFlg() == true)
						{
							soapbubble[j]->SoapBubbleSpawn(enemy[j]->GetLocation().x);
						}
					}
				}
			}

		for (int i = 0; i < now_floor_max; i++)
		{
			//プレイヤーが各オブジェクトのいずれかに着地している場合
			if (player->IsOnFloor(stagefloor[i]) == true)
			{
				//onshare_flgをtrueにする
				player->SetOnShareFlg(true);
			}
		}
		//敵の数だけ繰り返す
		for (int i = 0; i < max_enemy; i++)
		{
			for (int j = 0; j < now_floor_max; j++)
			{
				//敵が各オブジェクトのいずれかに着地している場合
				if (enemy[i]->IsOnFloor(stagefloor[j]) == true)
				{
					//onshare_flgをtrueにする
					enemy[i]->SetOnShareFlg(true);
				}
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
			if (player->GetPlayerState() < DEATH)
			{
				//捕食処理：ターゲットはプレイヤー
				fish->TargetPrey(player);
			}
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
				/*バグが発生しているためコメントアウト*/
				//if (enemy[i]->GetIsDie() == true)
				//{
				//	fish->NotAtSeaSurface();
				//}

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

		/*プレイヤー、敵がいるときさかなに食べられてプレイヤーが死んだ場合
		敵が範囲内にいるなら海面に上がってこないバグがある
		敵が範囲外に出た場合上がってこれる?*/
		for (int i = 0; i < max_enemy;)
		{
			//プレイヤーか敵のいずれも海面にいない場合海に戻る
			if (fish->CheckSeaSurface(player) == false &&
				fish->CheckSeaSurface(enemy[i]) == false)
			{
				if (i == max_enemy - 1)
				{
					fish->NotAtSeaSurface();
				}
				i++;
			}
			else
			{
				break;
			}
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

			//クリアチェック
			clear_flg = true;
			for (int i = 0; i < max_enemy; i++)
			{
				//敵一体でも生きていたらフラグを立てない
				if (enemy[i]->GetEnemyDeathFlg() == false && enemy[i]->GetFlg() == true)
				{
					clear_flg = false;
				}
			}
			//全員やられてたら
			if (clear_flg == true)
			{
				clear_wait = 180;
			}
		}
	}
	else
	{
		//敵全撃破演出
		if (--clear_wait <= 0)
		{
			if (stage < MAX_STAGE-1)
			{
				NextStage();
			}
			else
			{
				return new GameOver();
			}
		}

	}
	if (CheckSoundMem(GameStart_BGM) == FALSE) {
		if (CheckSoundMem(EnemuyMove_SE) == FALSE)
		{
			PlaySoundMem(EnemuyMove_SE, DX_PLAYTYPE_BACK);
		}
	}
	return this;
}

void GameMain::Draw()const
{
	DrawFormatString(240, 0, 0x00ff00, "%d", stage);

	////グリッド表示
	//for (int i = 25; i < SCREEN_WIDTH; i += 25)
	//{
	//	if (i % 100 == 0)
	//	{
	//		DrawLine(i, 0, i, SCREEN_HEIGHT, 0xff0000);
	//	}
	//	else
	//	{
	//		DrawLine(i, 0, i, SCREEN_HEIGHT, 0x00ff00);
	//	}
	//}
	////グリッド表示
	//for (int i = 25; i < SCREEN_HEIGHT; i += 25)
	//{
	//	if (i % 100 == 0)
	//	{
	//		DrawLine(0, i, SCREEN_WIDTH, i, 0xff0000);
	//	}
	//	else
	//	{
	//		DrawLine(0, i, SCREEN_WIDTH, i, 0x00ff00);
	//	}
	//}
	thunder->Draw(Pouse);
	switch (stage)
	{
	case 0:
		stagefloor[0]->DrawLandLeft();
		stagefloor[1]->DrawLandRight();
		stagefloor[2]->DrawFooting1();
		break;
	case 1:
		stagefloor[0]->DrawLandLeft();
		stagefloor[1]->DrawLandRight();
		stagefloor[2]->DrawFooting1();
		stagefloor[3]->DrawFooting2();
		stagefloor[4]->DrawFooting2();
		break;
	case 2:
		stagefloor[0]->DrawLandLeft();
		stagefloor[1]->DrawLandRight();
		stagefloor[2]->DrawFooting3();
		stagefloor[3]->DrawFooting5();

		stagewall[0]->DrawFooting4();
		stagewall[1]->DrawFooting4();
		stagewall[2]->DrawFooting4();
		break;
	case 3:
		stagefloor[0]->DrawLandLeft2();
		stagefloor[1]->DrawLandRight2();
		stagefloor[2]->DrawFooting6();
		stagefloor[3]->DrawFooting6();
		stagefloor[4]->DrawFooting6();
		stagefloor[5]->DrawFooting6();
		stagefloor[6]->DrawFooting6();
		break;
	case 4:
		stagefloor[0]->DrawLandLeft();
		stagefloor[1]->DrawLandRight();
		stagefloor[2]->DrawFooting6();
		stagefloor[3]->DrawFooting6();
		stagefloor[4]->DrawFooting6();

		stagewall[0]->DrawFooting7();
		stagewall[1]->DrawFooting7();
		stagewall[2]->DrawFooting8();
		break;
	default:
		break;
	}
	//デバッグ用　当たり判定表示
	for (BoxCollider* stagefloor : stagefloor)
	{
		stagefloor->Draw();
	}
	for (BoxCollider* stagewall : stagewall)
	{
		stagewall->Draw();
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
	ui->Draw(player->GetPlayerLife());
	DrawGraph(159, 444, seaImage, TRUE);
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

int GameMain::NextStage()
{
	if (++stage > MAX_STAGE)
	{
		return 0;
	}

	fish = new Fish();
	CreateStage(stage);
}

void GameMain::CreateStage(int stage)
{
	player->ResetPlayerPos();
	switch (stage)
	{
	case 0:
		now_floor_max = 3;
		stagefloor[0]->SetInit(0, 416, 30, 160, 5);
		stagefloor[1]->SetInit(479, 416, 30, 160, 5);
		stagefloor[2]->SetInit(180, 260, 18, 280, 0);

		thunder = new Thunder();

		max_enemy = 3;
		enemy[0] = new Enemy(SpawnPosSet(stagefloor[2]).x-70, SpawnPosSet(stagefloor[2]).y, 1);
		enemy[1] = new Enemy(SpawnPosSet(stagefloor[2]).x, SpawnPosSet(stagefloor[2]).y, 1);
		enemy[2] = new Enemy(SpawnPosSet(stagefloor[2]).x+70, SpawnPosSet(stagefloor[2]).y, 1);
		for (int i = 0; i < max_enemy; i++)
		{
			enemy_ai[i] = new ENEMY_AI;
			soapbubble[i] = new SoapBubble();
		}
		break;
	case 1:
		now_floor_max = 5;
		stagefloor[0]->SetInit(0, 416, 30, 160, 5);
		stagefloor[1]->SetInit(479, 416, 30, 160, 5);
		stagefloor[2]->SetInit(180, 260, 18, 280, 0);
		stagefloor[3]->SetInit(90, 150, 18, 120, 0);
		stagefloor[4]->SetInit(460, 130, 18, 120, 0);

		thunder = new Thunder();

		max_enemy = 5;
		enemy[0] = new Enemy(SpawnPosSet(stagefloor[3]).x, SpawnPosSet(stagefloor[3]).y, 2);
		enemy[1] = new Enemy(SpawnPosSet(stagefloor[4]).x, SpawnPosSet(stagefloor[4]).y, 2);
		enemy[2] = new Enemy(SpawnPosSet(stagefloor[2]).x - 70, SpawnPosSet(stagefloor[2]).y, 1);
		enemy[3] = new Enemy(SpawnPosSet(stagefloor[2]).x, SpawnPosSet(stagefloor[2]).y, 1);
		enemy[4] = new Enemy(SpawnPosSet(stagefloor[2]).x + 70, SpawnPosSet(stagefloor[2]).y, 1);
		for (int i = 0; i < max_enemy; i++)
		{
			enemy_ai[i] = new ENEMY_AI;
			soapbubble[i] = new SoapBubble();
		}
		break;
	case 2:
		now_floor_max = 7;
		stagefloor[0]->SetInit(0, 416, 30, 160, 5);
		stagefloor[1]->SetInit(479, 416, 30, 160, 5);
		stagefloor[2]->SetInit(270, 370, 18, 80, 0);
		stagefloor[3]->SetInit(200, 100, 18, 40, 0);
		stagefloor[4]->SetInit(160, 280, 18, 60, 0);
		stagefloor[5]->SetInit(310, 200, 18, 60, 0);
		stagefloor[6]->SetInit(490, 100, 18, 60, 0);

		//for (int i = 4; i < MAX_FLOOR; i++)
		//{
		//	stagefloor[i]->SetInit(-1, -1, 0, 0, 0);
		//}

		stagewall[0]->SetInit(160, 280, 18, 60, 0);
		stagewall[1]->SetInit(310, 200, 18, 60, 0);
		stagewall[2]->SetInit(490, 100, 18, 60, 0);



		thunder = new Thunder();

		max_enemy = 5;
		enemy[0] = new Enemy(SpawnPosSet(stagefloor[3]).x, SpawnPosSet(stagefloor[3]).y, 3);
		enemy[1] = new Enemy(SpawnPosSet(stagefloor[6]).x, SpawnPosSet(stagefloor[6]).y, 3);
		enemy[2] = new Enemy(SpawnPosSet(stagefloor[5]).x, SpawnPosSet(stagefloor[5]).y, 2);
		enemy[3] = new Enemy(SpawnPosSet(stagefloor[4]).x, SpawnPosSet(stagefloor[4]).y, 2);
		enemy[4] = new Enemy(SpawnPosSet(stagefloor[2]).x, SpawnPosSet(stagefloor[2]).y, 1);
		for (int i = 0; i < max_enemy; i++)
		{
			enemy_ai[i] = new ENEMY_AI;
			soapbubble[i] = new SoapBubble();
		}
		break;
	case 3:
		now_floor_max = 7;
		stagefloor[0]->SetInit(0, 416, 30, 160, 5);
		stagefloor[1]->SetInit(479, 416, 30, 160, 5);
		stagefloor[2]->SetInit(350, 370, 18, 60, 0);
		stagefloor[3]->SetInit(455, 270, 18, 60, 0);
		stagefloor[4]->SetInit(230, 290, 18, 60, 0);
		stagefloor[5]->SetInit(120, 250, 18, 60, 0);
		stagefloor[6]->SetInit(310, 180, 18, 60, 0);

		for (int i = 0; i < MAX_WALL; i++)
		{
			stagewall[i]->SetInit(-1, -1, 0, 0, 0);
		}

		thunder = new Thunder();

		max_enemy = 5;
		enemy[0] = new Enemy(SpawnPosSet(stagefloor[6]).x, SpawnPosSet(stagefloor[6]).y, 2);
		enemy[1] = new Enemy(SpawnPosSet(stagefloor[5]).x, SpawnPosSet(stagefloor[5]).y, 1);
		enemy[2] = new Enemy(SpawnPosSet(stagefloor[4]).x, SpawnPosSet(stagefloor[4]).y, 1);
		enemy[3] = new Enemy(SpawnPosSet(stagefloor[3]).x, SpawnPosSet(stagefloor[3]).y, 1);
		enemy[4] = new Enemy(SpawnPosSet(stagefloor[2]).x, SpawnPosSet(stagefloor[2]).y, 1);
		for (int i = 0; i < max_enemy; i++)
		{
			enemy_ai[i] = new ENEMY_AI;
			soapbubble[i] = new SoapBubble();
		}
		break;
	case 4:
		now_floor_max = 5;
		stagefloor[0]->SetInit(0, 416, 30, 160, 5);
		stagefloor[1]->SetInit(479, 416, 30, 160, 5);
		stagefloor[2]->SetInit(200, 325, 18, 60, 0);
		stagefloor[3]->SetInit(370, 325, 18, 60, 0);
		stagefloor[4]->SetInit(220, 80, 18, 60, 0);

		for (int i = 5; i < MAX_FLOOR; i++)
		{
			stagefloor[i]->SetInit(-1, -1, 0, 0, 0);
		}


		stagewall[0]->SetInit(100, 200, 50, 20, 0);
		stagewall[1]->SetInit(260, 170, 50, 20, 0);
		stagewall[2]->SetInit(500, 160, 70, 20, 0);

		thunder = new Thunder();

		max_enemy = 6;
		enemy[0] = new Enemy(SpawnPosSet(stagefloor[4]).x, SpawnPosSet(stagefloor[4]).y, 3);
		enemy[1] = new Enemy(SpawnPosSet(stagewall[0]).x, SpawnPosSet(stagewall[0]).y, 2);
		enemy[2] = new Enemy(SpawnPosSet(stagewall[1]).x, SpawnPosSet(stagewall[1]).y, 2);
		enemy[3] = new Enemy(SpawnPosSet(stagewall[2]).x, SpawnPosSet(stagewall[2]).y, 2);
		enemy[4] = new Enemy(SpawnPosSet(stagefloor[2]).x, SpawnPosSet(stagefloor[2]).y, 1);
		enemy[5] = new Enemy(SpawnPosSet(stagefloor[3]).x, SpawnPosSet(stagefloor[3]).y, 1);
		for (int i = 0; i < max_enemy; i++)
		{
			enemy_ai[i] = new ENEMY_AI;
			soapbubble[i] = new SoapBubble();
		}
		break;
	}
}

int GameMain::GetScore()
{
	return score;
}

Location GameMain::SpawnPosSet(StageFloor* floor)
{
	Location spawn;
	spawn.x = floor->GetLocation().x + (floor->GetArea().width / 2) - PLAYER_ENEMY_WIDTH /2 ;
	spawn.y = floor->GetLocation().y - PLAYER_ENEMY_HEIGHT;
	return spawn;
}

Location GameMain::SpawnPosSet(StageWall* wall)
{
	Location spawn;
	spawn.x = wall->GetLocation().x + (wall->GetArea().width / 2) - PLAYER_ENEMY_WIDTH / 2;
	spawn.y = wall->GetLocation().y - PLAYER_ENEMY_HEIGHT;
	return spawn;
}