#include <time.h>
#include "Dxlib.h"
#include "GameMain.h"
#include"GameOver.h"
#include"PadInput.h"


GameMain::GameMain()
{
	stage = 0;
	player = new Player();
	for (int i = 3; i < FLOOR_MAX; i++)
	{
		stagefloor[i] = new StageFloor(0, 0, 0, 0, 0);
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

	now_floor_max = 3;
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
	for (int i = 0; i < FLOOR_MAX; i++)
	{
		delete stagefloor[i];
	}
	delete thunder;
	DeleteGraph(seaImage);
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

			//プレイヤーがいずれかのオブジェクトに着地していない場合
			if (player->IsOnFloor(stagefloor) != true) 
			{
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

					//敵がいずれかのオブジェクトに着地していない場合
					if (enemy[i]->IsOnFloor(stagefloor) != true) 
					{
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
	stagefloor[0]->DrawLandLeft();
	stagefloor[1]->DrawLandRight();
	stagefloor[2]->DrawFooting1();
	thunder->Draw(Pouse);
	//デバッグ用　当たり判定表示
	//for (BoxCollider* stagefloor : stagefloor)
	//{
	//	stagefloor->Draw();
	//}
	if (Pouse == false) {
		player->Draw();

	}
	//if (Pouse == false) {
		for (int i = 0; i < max_enemy; i++)
		{
			enemy[i]->Draw();
			soapbubble[i]->Draw();
		}
	//}
	fish->Draw();
	ui->Draw();
	DrawGraph(159, 444, seaImage, TRUE);

	//スコア表示（仮）
	DrawNumber(170, 0, score);
	//スコア表示（仮）
	DrawNumber(350, 0, score);
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
		stagefloor[0] = new StageFloor(0, 416, 30, 160, 5);
		stagefloor[1] = new StageFloor(479, 416, 30, 160, 5);
		stagefloor[2] = new StageFloor(180, 260, 18, 280, 0);

		thunder = new Thunder();

		max_enemy = 3;
		for (int i = 0; i < max_enemy; i++)
		{
			enemy[i] = new Enemy(230 + i * 70, 210, 1);
			enemy_ai[i] = new ENEMY_AI;
			soapbubble[i] = new SoapBubble();
		}
		break;
	case 1:
		stagefloor[0] = new StageFloor(0, 416, 30, 160, 5);
		stagefloor[1] = new StageFloor(479, 416, 30, 160, 5);
		stagefloor[2] = new StageFloor(180, 260, 18, 280, 0);

		thunder = new Thunder();

		max_enemy = 5;
		enemy[0] = new Enemy(110, 80, 2);
		enemy[1] = new Enemy(510, 70, 2);
		enemy[2] = new Enemy(230, 210, 1);
		enemy[3] = new Enemy(300, 210, 1);
		enemy[4] = new Enemy(370, 210, 1);
		for (int i = 0; i < max_enemy; i++)
		{
			enemy_ai[i] = new ENEMY_AI;
			soapbubble[i] = new SoapBubble();
		}
		break;
	case 2:
		stagefloor[0] = new StageFloor(0, 416, 30, 160, 5);
		stagefloor[1] = new StageFloor(479, 416, 30, 160, 5);
		stagefloor[2] = new StageFloor(180, 260, 18, 280, 0);

		thunder = new Thunder();

		max_enemy = 5;
		enemy[0] = new Enemy(210, 30, 3);
		enemy[1] = new Enemy(550, 30, 3);
		enemy[2] = new Enemy(350, 100, 2);
		enemy[3] = new Enemy(200, 220, 2);
		enemy[4] = new Enemy(300, 300, 1);
		for (int i = 0; i < max_enemy; i++)
		{
			enemy_ai[i] = new ENEMY_AI;
			soapbubble[i] = new SoapBubble();
		}
		break;
	case 3:
		stagefloor[0] = new StageFloor(0, 416, 30, 160, 5);
		stagefloor[1] = new StageFloor(479, 416, 30, 160, 5);
		stagefloor[2] = new StageFloor(180, 260, 18, 280, 0);

		thunder = new Thunder();

		max_enemy = 5;
		enemy[0] = new Enemy(320, 130, 2);
		enemy[1] = new Enemy(140, 210, 1);
		enemy[2] = new Enemy(240, 240, 1);
		enemy[3] = new Enemy(450, 230, 1);
		enemy[4] = new Enemy(350, 320, 3);
		for (int i = 0; i < max_enemy; i++)
		{
			enemy_ai[i] = new ENEMY_AI;
			soapbubble[i] = new SoapBubble();
		}
		break;
	case 4:
		stagefloor[0] = new StageFloor(0, 416, 30, 160, 5);
		stagefloor[1] = new StageFloor(479, 416, 30, 160, 5);
		stagefloor[2] = new StageFloor(180, 260, 18, 280, 0);

		thunder = new Thunder();

		max_enemy = 6;
		enemy[0] = new Enemy(210, 20, 3);
		enemy[1] = new Enemy(90, 160, 2);
		enemy[2] = new Enemy(230, 110, 2);
		enemy[3] = new Enemy(450, 100, 2);
		enemy[4] = new Enemy(200, 300, 1);
		enemy[5] = new Enemy(350, 300, 1);
		for (int i = 0; i < max_enemy; i++)
		{
			enemy_ai[i] = new ENEMY_AI;
			soapbubble[i] = new SoapBubble();
		}
		break;
	}
}