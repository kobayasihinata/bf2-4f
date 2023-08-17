#include "Dxlib.h"
#include "GameMain.h"
#include "Title.h"
#include "BonusStage.h"
#include "PadInput.h"
#include "Pause.h"

static int score;      //���݂̃X�e�[�W��
static int stage;      //���݂̃X�e�[�W��

GameMain::GameMain(int beforescene)
{
	player = new Player();
	//�J�ڑO�̃X�e�[�W���^�C�g���Ȃ�
	if (beforescene == 0)
	{
		//�X�e�[�W�ƃX�R�A�̏������Z�b�g����
		DataReset();
		//�v���C���[�̏������Z�b�g����
		player->ResetPlayerLife();
	}
	for (int i = 0; i < MAX_FLOOR; i++)
	{
		stageobject[i] = new StageObject;
	}
	for (int i = 0; i < 2; i++)
	{
		thunder[i] = new Thunder(0, 0, false);
	}
	for (int i = 0; i < MAX_STAR; i++)
	{
		backgroundstar[i] = new BackGroundStar(stage);
	}
	NextStage();
	fish = new Fish();
	ui = new UI();
	soundmanager = new SoundManager();
	seaImage = LoadGraph("images/Stage/Stage_Sea01.png");
	phase_image = LoadGraph("images/UI/UI_Phase.png");
	main_state = Normal;
	Pouse = false;

	para = false;
	E_jump = false;

	for (int i = 0; i <= ENEMY_NAMBER; i++)
	{
		Avoidance[i] = FALSE;
	}
	damage_once = false;
	clear_flg = false;
	clear_wait = 0;
	phase_disptime = 0;
	phase_disp = 0;
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

	for (int i = 0; i < MAX_STAR; i++)
	{
		delete backgroundstar[i];
	}

	for (int i = 0; i < 2; i++)
	{
		delete thunder[i];
	}
	delete ui;
	DeleteGraph(seaImage);
	DeleteGraph(phase_image);
}

AbstractScene* GameMain::Update()
{
	soundmanager->Update();
	//�G�S���j��̉��o���Ŗ������
	switch (main_state)
	{
	case Normal:
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_START)) {
			soundmanager->Stop_All_Sound();
			Pouse = !Pouse;
		}
		if (Pouse == false) {
			for (Thunder* thunder : thunder)
			{
				thunder->Update();
				if (thunder->HitPlayer(player) == true && player->GetPlayerState() < DEATH)
				{
					player->SetThunderDeath(true);
					thunder->ReInitThunder();
				}
			}
			//���݂�stageobject�̐��������[�v����
			for (int i = 0; i < now_floor_max; i++)
			{
				for (Thunder* thunder : thunder)
				{
					thunder->Reflection(stageobject[i]);
				}

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
							}
							else {
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
				if (enemy[i]->GetEnemyJumpFlg() && E_jump == false) {
					soundmanager->PlayE_Move_SE();
					E_jump = true;
				}
				// �p���V���[�gSE
				if (enemy[i]->GetEnemyParaFlg() && para == false) {
					soundmanager->PlayPara_SE();
					para = true;
				}
				if (enemy[i]->GetE_Splash_SE_flg()) {
					soundmanager->PlaySplash_SE();
					enemy[i]->Reset_SE_flg1();
				}
				
				enemy[i]->Update();
				soapbubble[i]->Update();
				if (player->GetPlayerDeathFlg() == false)
				{
					score += soapbubble[i]->HitPlayerCollision(player);
				}

			}

			if (E_jump == false) {
				soundmanager->Stop_E_Move();
			}
			if (para == false) {
				soundmanager->Stop_Para();
			}
			
			E_jump = false;
			para = false;

			if (player->GetWalkFlg()) {
				soundmanager->PlayP_Walk_SE();
				player->ResetSEflg1();
			}
			if (player->GetJumpFlg()) {
				soundmanager->PlayP_Jump_SE();
				player->ResetSEflg2();
			}
			if (player->GetFallFlg()) {
				soundmanager->PlayFalling_SE();
				player->ResetSEflg3();
			}
			if (player->GetSplashSEflg()) {
				soundmanager->PlaySplash_SE();
				player->ResetSEflg4();
			}
			if (player->GetRestartSEflg()) {
				soundmanager->PlayRestart_SE();
				player->ResetSEflg5();
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
				//if (fish->GetTargetIsEnemy())
				//{
				//	fish->SetTargetFlg(true);
				//}
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
					soundmanager->PlayEatable_SE();
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

					fish->SetTarget(enemy[i]);

					//�C�ʂɓG�̂����ꂩ������ꍇ
					if (fish->CheckSeaSurface(enemy[i]) == true && enemy[i]->GetEnemyState() < DEATH_RIGHT)
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
							enemy[i]->SetParaFlg(false);
							enemy[i]->SetFlg(false);
							enemy[i]->SetIsDie(true);
							soundmanager->PlayEatable_SE();
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
				soundmanager->PlayStageClear_SE();
				main_state = Clear;
				clear_wait = 180;
			}
			//�v���C���[�̎c�@��0��菬�����ꍇ�^�C�g���ɖ߂�
			if (player->GetPlayerLife() < 0)
			{
				main_state = Over;
				GameOver_Img = LoadGraph("images/UI/UI_GameOver.png");
				soundmanager->PlayGameOver_SE();
				WaitTimer = SECOND_TO_FRAME(4);
			}
			//�w�i�̐��`��p����
			for (int i = 0; i < MAX_STAR; i++)
			{
				backgroundstar[i]->Update();
			}

			//���݂̃X�e�[�W���`��p
			if (++phase_disptime > 300)
			{
				phase_disptime = 301;
			}
			else
			{
				if (++phase_disp > 60)
				{
					phase_disp = 0;
				}
			}
		}
		break;
	case Clear:
		//�G�S���j���o
		if (--clear_wait <= 0)
		{
			if (stage < MAX_STAGE - 1)
			{
				soundmanager->Reset_flg();
				soundmanager->Stop_All_Sound();
				phase_disptime = 0;
				stage++;
				if (stage == 3)
				{
					return new BonusStage();
				}
				NextStage();
			}
			else
			{
				main_state = Over;
				GameOver_Img = LoadGraph("images/UI/UI_GameOver.png");
				soundmanager->PlayGameOver_SE();
				WaitTimer = SECOND_TO_FRAME(4);
			}
		}
		break;
	case Over:
		//PAD_INPUT::UpdateKey();
		if (--WaitTimer <= 0 || PAD_INPUT::OnButton(XINPUT_BUTTON_START)) {
			if (GameMain::GetScore() > ui->GetHighScore())
			{
				UI::SaveHighScore();
			}
			DataReset();
			return new Title();
		}
		break;
	default:
		break;
	}
	return this;
}

void GameMain::Draw()const
{
	for (int i = 0; i < MAX_STAR; i++)
	{
		backgroundstar[i]->Draw();
	}
	
	for (int i = 0; i < 2; i++)
	{
		thunder[i]->Draw(Pouse);
	}

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
		stageobject[0]->DrawLandLeft2();
		stageobject[1]->DrawLandRight2();
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
	////�f�o�b�O�p�@�����蔻��\��
	//for (BoxCollider* stageobject : stageobject)
	//{
	//	stageobject->Draw();
	//}
	if (Pouse == false && main_state != Over) {
		player->Draw();

	}
	if (Pouse == false) {
		for (int i = 0; i < max_enemy; i++)
		{
			enemy[i]->Draw();
			soapbubble[i]->Draw();
			//DrawFormatString(0, 0 + (i * 20), 0x00ff00, "%d", enemy[i]->GetEnemyParaFlg());
		}
	}
	fish->Draw();
	ui->Draw(player->GetPlayerLife());
	if (phase_disptime < 300)
	{
		if (phase_disp < 30)
		{
			DrawGraph(170, 30, phase_image, true);
			ui->DrawNumber(285, 20, stage + 1, 2);
		}
	}
	DrawGraph(159, 444, seaImage, TRUE);

	if (main_state == Over) {
		DrawGraph(221, 233, GameOver_Img, 1);
	}
}

void GameMain::Damage(int i)
{
	//�v���C���[��25��̍��W�ɓG������Ȃ�v���C���[�̕��D�����炷
	if (enemy[i]->GetLocation().y + 25 < player->GetLocation().y && enemy[i]->GetEnemyParaFlg() == false && enemy[i]->GetWaitFlg() == false && damage_once == false)
	{
		player->BalloonDec();
		damage_once = true;
		soundmanager->PlayCrack_SE();
	}
	else
	{
		damage_once = false;
	}

	//�v���C���[��25���̍��W�ɓG������Ȃ�G�̕��D�����炷
	if (enemy[i]->GetLocation().y > player->GetLocation().y + BALLOON_HEIGHT)
	{
		score += enemy[i]->ApplyDamege();
		if (enemy[i]->GetEnemyParaFlg()) {
			soundmanager->PlayDefeatTheEnemy_SE();
		} else {
			soundmanager->PlayCrack_SE();
		}
	}

	//�G�����D��c��܂���O�Ȃ瓷�̂ɐڐG���Ă��_���[�W������
	if (enemy[i]->GetWaitFlg() == true)
	{
		score += enemy[i]->ApplyDamege();
		soundmanager->PlayDefeatTheEnemy_SE();
	}
}

void GameMain::NextStage()
{
	for (int i = 0; i < MAX_STAR; i++)
	{
		backgroundstar[i]->GetType(stage);
	}
	fish = new Fish();
	CreateStage(stage);

	main_state = Normal;
}

void GameMain::CreateStage(int stage)
{
	player->ResetPlayerPos(PLAYER_RESPAWN_POS_X, PLAYER_RESPAWN_POS_Y);
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

		thunder[0] = new Thunder(300, 70, true);
		thunder[1] = new Thunder(0, 0, false);

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
		stageobject[3]->SetInit(80, 150, 18, 120, 0);
		stageobject[4]->SetInit(450, 130, 18, 120, 0);

		for (int i = 5; i < MAX_FLOOR; i++)
		{
			stageobject[i]->SetInit(-1, -1, 0, 0, 0);
		}

		thunder[0] = new Thunder(50, 210, true);
		thunder[1] = new Thunder(460, 185, true);
		
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

		stageobject[7]->SetInit(180, 298, 52, 20, 0);
		stageobject[8]->SetInit(330, 218, 52, 20, 0);
		stageobject[9]->SetInit(510, 118, 52, 20, 0);


		thunder[0] = new Thunder(50, 120, true);
		thunder[1] = new Thunder(420, 250, true);		/*�����Q�o�O�H*/

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

		for (int i = now_floor_max; i < MAX_FLOOR; i++)
		{
			stageobject[i]->SetInit(-1, -1, 0, 0, 0);
		}

		thunder[0] = new Thunder(130, 80, true);		/*�����R�C�ւ����Ȃ�*/
		thunder[1] = new Thunder(450, 150, true);

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
		stageobject[5]->SetInit(100, 200, 50, 20, 0);
		stageobject[6]->SetInit(260, 170, 50, 20, 0);
		stageobject[7]->SetInit(500, 160, 70, 20, 0);

		for (int i = now_floor_max; i < MAX_FLOOR; i++)
		{
			stageobject[i]->SetInit(-1, -1, 0, 0, 0);
		}


		thunder[0] = new Thunder(60, 80, true);		/*����1�C�ւ����Ȃ��Q�C�ւ����Ȃ��R�o�O�H*/
		thunder[1] = new Thunder(340, 120, true);	/*�����O�o�O�H*/

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

int GameMain::GetScore()
{
	return score;
}

void GameMain::AddScore(int point)
{
	score += point;
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
void GameMain::DataReset()
{
	score = 0;
	stage = 0;
}