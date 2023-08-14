#include "Dxlib.h"
#include "GameMain.h"
#include "Title.h"
#include"PadInput.h"
#include"Pause.h"



GameMain::GameMain()
{
	stage = 0;
	player = new Player();
	for (int i = 0; i < MAX_FLOOR; i++)
	{
		stageobject[i] = new StageObject;
	}
	CreateStage(stage);
	fish = new Fish();
	ui = new UI();
	seaImage = LoadGraph("images/Stage/Stage_Sea01.png");
	GameStart_BGM = LoadSoundMem("sounds/SE_Start.wav");
	Eatable_SE = LoadSoundMem("sounds/SE_Eatable.wav");
	StageClear_SE = LoadSoundMem("sounds/SE_StageClear.wav");
	PlaySoundMem(GameStart_BGM, DX_PLAYTYPE_BACK);

	main_state = Normal;
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
		delete stageobject[i];
	}
	delete thunder;
	DeleteGraph(seaImage);
}

AbstractScene* GameMain::Update()
{
	//�G�S���j��̉��o���Ŗ������
	switch (main_state)
	{
	case Normal:
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
			//���݂�stageobject�̐��������[�v����
			for (int i = 0; i < now_floor_max; i++)
			{
				thunder->Reflection(stageobject[i]);
				//�v���C���[�����S���łȂ��Ȃ�
				if (player->GetPlayerDeathFlg() == false && player->GetThunderDeathFlg() == false)
				{
					//�e�I�u�W�F�N�g�Ƃ̓����蔻�菈��
					player->HitStageCollision(stageobject[i]);
					//���݈ʒu�擾
					P_x = player->GetPlayerLocation().x;
					P_y = player->GetPlayerLocation().y;
				}

				//�v���C���[�������ꂩ�̃I�u�W�F�N�g�ɒ��n���Ă��Ȃ��ꍇ
				if (player->IsOnFloor(stageobject[i]) != true)
				{
					//onshare_flg��false�ɂ���
					player->SetOnShareFlg(false);
				}

				for (int j = 0; j < max_enemy; j++)
				{
					if (enemy[j]->GetFlg() == true)
					{
						int E_x = enemy[j]->GetEnemyLocation().x;
						int E_y = enemy[j]->GetEnemyLocation().y;
						//�G�����S���łȂ�������ł��Ȃ��Ȃ�
						if (enemy[j]->GetEnemyDeathFlg() == false)
						{

							//�e�I�u�W�F�N�g�Ƃ̓����蔻�菈��
							enemy[j]->HitStageCollision(stageobject[i]);

							if (enemy[j]->No_AI_Flg() == 0)
							{
								if (enemy_ai[j]->AI_Cool_Update() <= 0)
								{
									//�GAI�擾
									if (player->GetPlayerRespawn() <= 0)
									{
										AI_Pattern[j] = enemy_ai[j]->Update(P_x, P_y, E_x, E_y);
										//AI�N�[���^�C���Z�b�g
										enemy_ai[j]->Set_AI_Cool(enemy[j]->GetEnemyLevel());
									}
									else {
										AI_Pattern[j] = enemy_ai[j]->Move_Rand();
										//AI�N�[���^�C���Z�b�g
										enemy_ai[j]->Set_AI_Cool(2);
									}
								}

								// �p�^�[���ɂ���čs����ς���
								switch (AI_Pattern[j])
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
							} else {
								enemy_ai[j]->Set_AI_Cool(0);
							}
							
							// �v���C���[���^��ɗ���Ɖ��
							if (E_x >= P_x - 50 && E_x <= P_x + 50 && E_y >= P_y && E_y < P_y + 100 && Avoidance[j] == FALSE)
							{
								Avoidance[j] = TRUE;
								enemy_ai[j]->Set_AI_Cool(enemy[j]->GetEnemyLevel());
							}
							if (Avoidance[j] == TRUE) {
								if ((E_x < P_x - 150 && E_x > P_x + 150) || (E_y < P_y - 50 || E_y >= P_y + 100)) {
									Avoidance[j] = FALSE;
								}
							}
						}

						//�G�������ꂩ�̃I�u�W�F�N�g�ɒ��n���Ă��Ȃ��ꍇ
						if (enemy[j]->IsOnFloor(stageobject[j]) != true)
						{
							//onshare_flg��false�ɂ���
							enemy[j]->SetOnShareFlg(false);
						}

						//�G�����S���[�V�������Ŗ������v���C���[�����S���o���Ŗ����Ȃ�
						if (enemy[j]->GetEnemyDeathFlg() == false && player->GetThunderDeathFlg() == false && player->GetPlayerDeathFlg() == false)
						{
							//�v���C���[�����G��ԂłȂ��Ȃ�
							if (player->GetPlayerRespawn() <= 0)
							{
								//�v���C���[�ƓG�̓����蔻��
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
						}

						//�G�����v���Ȃ�
						if (enemy[j]->GetEnemyUnderWaterFlg() == true)
						{
							soapbubble[j]->SoapBubbleSpawn(enemy[j]->GetLocation().x);
						}
					}
				}
			}
			for (int j = 0; j < max_enemy; j++)
			{
				//�G�ƓG�̓����蔻��
				for (int k = j + 1; k < max_enemy; k++)
				{
					//�G�������Ă���Ȃ�
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
		for (int i = 0; i < now_floor_max; i++)
		{
			//�v���C���[���e�I�u�W�F�N�g�̂����ꂩ�ɒ��n���Ă���ꍇ
			if (player->IsOnFloor(stageobject[i]) == true)
			{
				//onshare_flg��true�ɂ���
				player->SetOnShareFlg(true);
			}
		}
		//�G�̐������J��Ԃ�
		for (int i = 0; i < max_enemy; i++)
		{
			for (int j = 0; j < now_floor_max; j++)
			{
				//�G���e�I�u�W�F�N�g�̂����ꂩ�ɒ��n���Ă���ꍇ
				if (enemy[i]->IsOnFloor(stageobject[j]) == true)
				{
					//onshare_flg��true�ɂ���
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

			//�v���C���[������ł���ꍇ�C�ɖ߂�
			if (player->GetIsDie() == true)
			{
				fish->NotAtSeaSurface();
			}

			//�C�ʂɃv���C���[������ꍇ
			if (fish->CheckSeaSurface(player) == true)
			{
				if (player->GetPlayerState() < DEATH)
				{
					//�ߐH�����F�^�[�Q�b�g�̓v���C���[
					fish->TargetPrey(player);
				}
				//�v���C���[���ߐH���ꂽ�ꍇ
				//�摜���\���ɂ��Ď���ł��锻��ɂ���
				if (fish->GetIsPreyedOnPlayer() == true)
				{
					player->SetShowFlg(false);
					player->SetIsDie(true);
					PlaySoundMem(Eatable_SE, DX_PLAYTYPE_BACK);
				}
			}
			else
			{
				for (int i = 0; i < max_enemy; i++)
				{
					/*�o�O���������Ă��邽�߃R�����g�A�E�g*/
					//if (enemy[i]->GetIsDie() == true)
					//{
					//	fish->NotAtSeaSurface();
					//}

						//�C�ʂɓG�̂����ꂩ������ꍇ
					if (fish->CheckSeaSurface(enemy[i]) == true)
					{
						//�G�̃��x�����擾����
						fish->SetSaveEnemyLevel(enemy[i]->GetEnemyLevel());

						//�ߐH�����F�^�[�Q�b�g�͓G
						fish->TargetPrey(enemy[i]);

						//�G���ߐH���ꂽ�ꍇ
						//�摜���\���ɂ���enemy��flg��false�ɂ���
						if (fish->GetIsPreyedOnEnemyr() == true)
						{
							enemy[i]->SetEnemyUnderWaterFlg(false);
							enemy[i]->SetShowFlg(false);
							enemy[i]->SetFlg(false);
							enemy[i]->SetIsDie(true);
							PlaySoundMem(Eatable_SE, DX_PLAYTYPE_BACK);
						}
						//�O�̂��ߎ���ł��锻��ɂ���
						if (enemy[i]->GetShowFlg() == false)
						{
							enemy[i]->SetIsDie(true);
							enemy[i]->SetFlg(false);
						}
					}
				}

			}

			/*�v���C���[�A�G������Ƃ������ȂɐH�ׂ��ăv���C���[�����񂾏ꍇ
			�G���͈͓��ɂ���Ȃ�C�ʂɏオ���Ă��Ȃ��o�O������
			�G���͈͊O�ɏo���ꍇ�オ���Ă����?*/
			for (int i = 0; i < max_enemy;)
			{
				//�v���C���[���G�̂�������C�ʂɂ��Ȃ��ꍇ�C�ɖ߂�
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

			//�����ȑ��Ńv���C���[�̃X�|�[���t���O����������
			if (fish->GetRespawnFlg() == true)
			{
				player->SetShowFlg(true);
				player->SetPlayerLife(-1);
				player->SetIsDie(false);
				player->PlayerRespawn(PLAYER_RESPAWN_POS_X, PLAYER_RESPAWN_POS_Y);
				fish->SetRespawnFlg(false);
			}

			//�N���A�`�F�b�N
			clear_flg = true;
			if (CheckSoundMem(StageClear_BGM) == FALSE)
			{
				PlaySoundMem(StageClear_BGM, DX_PLAYTYPE_BACK);
			}
			for (int i = 0; i < max_enemy; i++)
			{
				//�G��̂ł������Ă�����t���O�𗧂ĂȂ�
				if (enemy[i]->GetEnemyDeathFlg() == false && enemy[i]->GetFlg() == true)
				{
					clear_flg = false;
				}
			}
			//�S������Ă���
			if (clear_flg == true)
			{
				PlaySoundMem(StageClear_SE, DX_PLAYTYPE_BACK);
				main_state = Clear;
				clear_wait = 180;
			}
			//�v���C���[�̎c�@��0��菬�����ꍇ�^�C�g���ɖ߂�
			if (player->GetPlayerLife() < 0)
			{
				main_state = Over;
				GameOver_Img = LoadGraph("images/UI/UI_GameOver.png");
				GameOver_BGM = LoadSoundMem("sounds/SE_GameOver.wav");
				PlaySoundMem(GameOver_BGM, DX_PLAYTYPE_BACK);
				WaitTimer = SECOND_TO_FRAME(4);
			}
		}
		break;
	case Clear:
		//�G�S���j���o
		if (--clear_wait <= 0)
		{
			if (stage < MAX_STAGE - 1)
			{
				NextStage();
			}
			else
			{
				main_state = Over;
				GameOver_Img = LoadGraph("images/UI/UI_GameOver.png");
				GameOver_BGM = LoadSoundMem("sounds/SE_GameOver.wav");
				PlaySoundMem(GameOver_BGM, DX_PLAYTYPE_BACK);
				WaitTimer = SECOND_TO_FRAME(4);
			}
		}
		break;
	case Over:
		PAD_INPUT::UpdateKey();
		if (--WaitTimer <= 0 || PAD_INPUT::OnButton(XINPUT_BUTTON_START)) {
			return new Title();
		}
		break;
	default:
		break;
	}
	if (CheckSoundMem(GameStart_BGM) == FALSE) {
		
	}
	return this;
}

void GameMain::Draw()const
{
	DrawFormatString(240, 0, 0x00ff00, "%d", stage);

	////�O���b�h�\��
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
	////�O���b�h�\��
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
		stageobject[0]->DrawLandLeft();
		stageobject[1]->DrawLandRight();
		stageobject[2]->DrawFooting1();
		break;
	case 1:
		stageobject[0]->DrawLandLeft();
		stageobject[1]->DrawLandRight();
		stageobject[2]->DrawFooting1();
		stageobject[3]->DrawFooting2();
		stageobject[4]->DrawFooting2();
		break;
	case 2:
		stageobject[0]->DrawLandLeft();
		stageobject[1]->DrawLandRight();
		stageobject[2]->DrawFooting3();
		stageobject[3]->DrawFooting5();

		stageobject[4]->DrawFooting4();
		stageobject[5]->DrawFooting4();
		stageobject[6]->DrawFooting4();
		break;
	case 3:
		stageobject[0]->DrawLandLeft2();
		stageobject[1]->DrawLandRight2();
		stageobject[2]->DrawFooting6();
		stageobject[3]->DrawFooting6();
		stageobject[4]->DrawFooting6();
		stageobject[5]->DrawFooting6();
		stageobject[6]->DrawFooting6();
		break;
	case 4:
		stageobject[0]->DrawLandLeft();
		stageobject[1]->DrawLandRight();
		stageobject[2]->DrawFooting6();
		stageobject[3]->DrawFooting6();
		stageobject[4]->DrawFooting6();

		stageobject[5]->DrawFooting7();
		stageobject[6]->DrawFooting7();
		stageobject[7]->DrawFooting8();
		break;
	default:
		break;
	}
	//�f�o�b�O�p�@�����蔻��\��
	for (BoxCollider* stageobject : stageobject)
	{
		stageobject->Draw();
	}
	if (Pouse == false && main_state != Over) {
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
	ui->Draw();
	DrawGraph(159, 444, seaImage, TRUE);

	//�X�R�A�\���i���j
	DrawNumber(170, 0, score);
	//�X�R�A�\���i���j
	DrawNumber(350, 0, score);

	if (main_state == Over) {
		DrawGraph(221, 233, GameOver_Img, 1);
	}
}

void GameMain::Damage(int i)
{
	//�v���C���[��25��̍��W�ɓG������Ȃ�v���C���[�̕��D�����炷
	if (enemy[i]->GetLocation().y + BALLOON_HEIGHT < player->GetLocation().y && enemy[i]->GetEnemyParaFlg() == false && damage_once == false)
	{
		player->BalloonDec();
		damage_once = true;
	}

	//�v���C���[��25���̍��W�ɓG������Ȃ�v���C���[�̕��D�����炷
	if (enemy[i]->GetLocation().y > player->GetLocation().y + BALLOON_HEIGHT)
	{
		score += enemy[i]->ApplyDamege();
	}

	//�G�����D��c��܂���O�Ȃ瓷�̂ɐڐG���Ă��_���[�W������
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
	main_state = Normal;
}

void GameMain::CreateStage(int stage)
{
	player->ResetPlayerPos();
	switch (stage)
	{
	case 0:
		now_floor_max = 3;
		stageobject[0]->SetInit(0, 416, 30, 160, 5);
		stageobject[1]->SetInit(479, 416, 30, 160, 5);
		stageobject[2]->SetInit(180, 260, 18, 280, 0);

		for (int i = 3; i < MAX_FLOOR; i++)
		{
			stageobject[i]->SetInit(-1, -1, 0, 0, 0);
		}

		thunder = new Thunder();

		max_enemy = 3;
		enemy[0] = new Enemy(SpawnPosSet(stageobject[2]).x-70, SpawnPosSet(stageobject[2]).y, 1);
		enemy[1] = new Enemy(SpawnPosSet(stageobject[2]).x, SpawnPosSet(stageobject[2]).y, 1);
		enemy[2] = new Enemy(SpawnPosSet(stageobject[2]).x+70, SpawnPosSet(stageobject[2]).y, 1);
		for (int i = 0; i < max_enemy; i++)
		{
			enemy_ai[i] = new ENEMY_AI;
			soapbubble[i] = new SoapBubble();
		}
		break;
	case 1:
		now_floor_max = 5;
		stageobject[0]->SetInit(0, 416, 30, 160, 5);
		stageobject[1]->SetInit(479, 416, 30, 160, 5);
		stageobject[2]->SetInit(180, 260, 18, 280, 0);
		stageobject[3]->SetInit(90, 150, 18, 120, 0);
		stageobject[4]->SetInit(460, 130, 18, 120, 0);

		for (int i = 5; i < MAX_FLOOR; i++)
		{
			stageobject[i]->SetInit(-1, -1, 0, 0, 0);
		}

		thunder = new Thunder();

		max_enemy = 5;
		enemy[0] = new Enemy(SpawnPosSet(stageobject[3]).x, SpawnPosSet(stageobject[3]).y, 2);
		enemy[1] = new Enemy(SpawnPosSet(stageobject[4]).x, SpawnPosSet(stageobject[4]).y, 2);
		enemy[2] = new Enemy(SpawnPosSet(stageobject[2]).x - 70, SpawnPosSet(stageobject[2]).y, 1);
		enemy[3] = new Enemy(SpawnPosSet(stageobject[2]).x, SpawnPosSet(stageobject[2]).y, 1);
		enemy[4] = new Enemy(SpawnPosSet(stageobject[2]).x + 70, SpawnPosSet(stageobject[2]).y, 1);
		for (int i = 0; i < max_enemy; i++)
		{
			enemy_ai[i] = new ENEMY_AI;
			soapbubble[i] = new SoapBubble();
		}
		break;
	case 2:
		now_floor_max = 10;
		stageobject[0]->SetInit(0, 416, 30, 160, 5);
		stageobject[1]->SetInit(479, 416, 30, 160, 5);
		stageobject[2]->SetInit(270, 370, 18, 80, 0);
		stageobject[3]->SetInit(200, 100, 18, 40, 0);

		stageobject[4]->SetInit(160, 280, 18, 60, 0);
		stageobject[5]->SetInit(310, 200, 18, 60, 0);
		stageobject[6]->SetInit(490, 100, 18, 60, 0);

		stageobject[7]->SetInit(180, 280, 70, 20, 0);
		stageobject[8]->SetInit(330, 200, 70, 20, 0);
		stageobject[9]->SetInit(510, 100, 70, 20, 0);



		thunder = new Thunder();

		max_enemy = 5;
		enemy[0] = new Enemy(SpawnPosSet(stageobject[3]).x, SpawnPosSet(stageobject[3]).y, 3);
		enemy[1] = new Enemy(SpawnPosSet(stageobject[6]).x, SpawnPosSet(stageobject[6]).y, 3);
		enemy[2] = new Enemy(SpawnPosSet(stageobject[5]).x, SpawnPosSet(stageobject[5]).y, 2);
		enemy[3] = new Enemy(SpawnPosSet(stageobject[4]).x, SpawnPosSet(stageobject[4]).y, 2);
		enemy[4] = new Enemy(SpawnPosSet(stageobject[2]).x, SpawnPosSet(stageobject[2]).y, 1);
		for (int i = 0; i < max_enemy; i++)
		{
			enemy_ai[i] = new ENEMY_AI;
			soapbubble[i] = new SoapBubble();
		}
		break;
	case 3:
		now_floor_max = 7;
		stageobject[0]->SetInit(0, 416, 30, 160, 5);
		stageobject[1]->SetInit(479, 416, 30, 160, 5);
		stageobject[2]->SetInit(350, 370, 18, 60, 0);
		stageobject[3]->SetInit(455, 270, 18, 60, 0);
		stageobject[4]->SetInit(230, 290, 18, 60, 0);
		stageobject[5]->SetInit(120, 250, 18, 60, 0);
		stageobject[6]->SetInit(310, 180, 18, 60, 0);

		for (int i = 7; i < MAX_FLOOR; i++)
		{
			stageobject[i]->SetInit(-1, -1, 0, 0, 0);
		}

		thunder = new Thunder();

		max_enemy = 5;
		enemy[0] = new Enemy(SpawnPosSet(stageobject[6]).x, SpawnPosSet(stageobject[6]).y, 2);
		enemy[1] = new Enemy(SpawnPosSet(stageobject[5]).x, SpawnPosSet(stageobject[5]).y, 1);
		enemy[2] = new Enemy(SpawnPosSet(stageobject[4]).x, SpawnPosSet(stageobject[4]).y, 1);
		enemy[3] = new Enemy(SpawnPosSet(stageobject[3]).x, SpawnPosSet(stageobject[3]).y, 1);
		enemy[4] = new Enemy(SpawnPosSet(stageobject[2]).x, SpawnPosSet(stageobject[2]).y, 1);
		for (int i = 0; i < max_enemy; i++)
		{
			enemy_ai[i] = new ENEMY_AI;
			soapbubble[i] = new SoapBubble();
		}
		break;
	case 4:
		now_floor_max = 8;
		stageobject[0]->SetInit(0, 416, 30, 160, 5);
		stageobject[1]->SetInit(479, 416, 30, 160, 5);
		stageobject[2]->SetInit(200, 325, 18, 60, 0);
		stageobject[3]->SetInit(370, 325, 18, 60, 0);
		stageobject[4]->SetInit(220, 80, 18, 60, 0);

		for (int i = 5; i < MAX_FLOOR; i++)
		{
			stageobject[i]->SetInit(-1, -1, 0, 0, 0);
		}


		stageobject[5]->SetInit(100, 200, 50, 20, 0);
		stageobject[6]->SetInit(260, 170, 50, 20, 0);
		stageobject[7]->SetInit(500, 160, 70, 20, 0);

		thunder = new Thunder();

		max_enemy = 6;
		enemy[0] = new Enemy(SpawnPosSet(stageobject[4]).x, SpawnPosSet(stageobject[4]).y, 3);
		enemy[1] = new Enemy(SpawnPosSet(stageobject[5]).x, SpawnPosSet(stageobject[5]).y, 2);
		enemy[2] = new Enemy(SpawnPosSet(stageobject[6]).x, SpawnPosSet(stageobject[6]).y, 2);
		enemy[3] = new Enemy(SpawnPosSet(stageobject[7]).x, SpawnPosSet(stageobject[7]).y, 2);
		enemy[4] = new Enemy(SpawnPosSet(stageobject[2]).x, SpawnPosSet(stageobject[2]).y, 1);
		enemy[5] = new Enemy(SpawnPosSet(stageobject[3]).x, SpawnPosSet(stageobject[3]).y, 1);
		for (int i = 0; i < max_enemy; i++)
		{
			enemy_ai[i] = new ENEMY_AI;
			soapbubble[i] = new SoapBubble();
		}
		break;
	}
}

Location GameMain::SpawnPosSet(StageObject* floor)
{
	Location spawn;
	spawn.x = floor->GetLocation().x + (floor->GetArea().width / 2) - PLAYER_ENEMY_WIDTH /2 ;
	spawn.y = floor->GetLocation().y - PLAYER_ENEMY_HEIGHT;
	return spawn;
}

//Location GameMain::SpawnPosSet(StageObject* wall)
//{
//	Location spawn;
//	spawn.x = wall->GetLocation().x + (wall->GetArea().width / 2) - PLAYER_ENEMY_WIDTH / 2;
//	spawn.y = wall->GetLocation().y - PLAYER_ENEMY_HEIGHT;
//	return spawn;
//}