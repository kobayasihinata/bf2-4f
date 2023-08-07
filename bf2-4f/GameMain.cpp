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
		//stagefloor�͈̔͂������[�v����
		for (BoxCollider* stagefloor : stagefloor)
		{
			thunder->Reflection(stagefloor);
			//�v���C���[�����S���łȂ��Ȃ�
			if (player->GetPlayerDeathFlg() == false && player->GetThunderDeathFlg() == false)
			{
				//�e�I�u�W�F�N�g�Ƃ̓����蔻�菈��
				player->HitStageCollision(stagefloor);
				//���݈ʒu�擾
				P_x = player->GetPlayerLocation().x;
				P_y = player->GetPlayerLocation().y;
			}

			//�v���C���[���ǂ̃I�u�W�F�N�g�Ƃ����n���Ă��Ȃ��ꍇ
			if (player->IsOnFloor(stagefloor) != true) {
				//onshare_flg��false�ɂ���
				player->SetOnShareFlg(false);
			}

			for (int i = 0; i < max_enemy; i++)
			{
				if (enemy[i]->GetFlg() == true)
				{
					int E_x = enemy[i]->GetEnemyLocation().x;
					int E_y = enemy[i]->GetEnemyLocation().y;
					//�G�����S���łȂ�������ł��Ȃ��Ȃ�
					if (enemy[i]->GetEnemyDeathFlg() == false)
					{

						//�e�I�u�W�F�N�g�Ƃ̓����蔻�菈��
						enemy[i]->HitStageCollision(stagefloor);
						enemy_ai[i]->Update_AI_Cool();

						if (enemy[i]->No_AI_Flg() == 0)
						{
							//�G��AI�擾
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

					//�G���ǂ̃I�u�W�F�N�g�Ƃ����n���Ă��Ȃ��ꍇ
					if (enemy[i]->IsOnFloor(stagefloor) != true) {
						//onshare_flg��false�ɂ���
						enemy[i]->SetOnShareFlg(false);
					}

					//�G�����S���[�V�������Ŗ������v���C���[�����S���o���Ŗ����Ȃ�
					if (enemy[i]->GetEnemyDeathFlg() == false && player->GetThunderDeathFlg() == false && player->GetPlayerDeathFlg() == false)
					{
						//�v���C���[�����G��ԂłȂ��Ȃ�
						if (player->GetPlayerRespawn() <= 0)
						{
							//�v���C���[�ƓG�̓����蔻��
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

						//�G�ƓG�̓����蔻��
						for (int j = i + 1; j < max_enemy; j++)
						{
							//�G�������Ă���Ȃ�
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

					//�G�����v���Ȃ�
					if (enemy[i]->GetEnemyUnderWaterFlg() == true)
					{
						soapbubble[i]->SoapBubbleSpawn(enemy[i]->GetLocation().x);
					}
				}
			}
		}

		//�v���C���[���e�I�u�W�F�N�g�̂����ꂩ�ɒ��n���Ă���ꍇ
		if (player->IsOnFloor(stagefloor[0]) == true ||
			player->IsOnFloor(stagefloor[1]) == true ||
			player->IsOnFloor(stagefloor[2]) == true)
		{
			//onshare_flg��true�ɂ���
			player->SetOnShareFlg(true);
		}
		//�G�̐������J��Ԃ�
		for (int i = 0; i < max_enemy; i++)
		{
			//�G���e�I�u�W�F�N�g�̂����ꂩ�ɒ��n���Ă���ꍇ
			if (enemy[i]->IsOnFloor(stagefloor[0]) == true ||
				enemy[i]->IsOnFloor(stagefloor[1]) == true ||
				enemy[i]->IsOnFloor(stagefloor[2]) == true)
			{
				//onshare_flg��true�ɂ���
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

		//�v���C���[������ł���ꍇ�C�ɖ߂�
		if (player->GetIsDie() == true)
		{
			fish->NotAtSeaSurface();
		}

		//�C�ʂɃv���C���[������ꍇ
		if (fish->CheckSeaSurface(player) == true)
		{
			//�ߐH�����F�^�[�Q�b�g�̓v���C���[
			fish->TargetPrey(player);
			//�v���C���[���ߐH���ꂽ�ꍇ
			//�摜���\���ɂ��Ď���ł��锻��ɂ���
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

		//�v���C���[���G�̂�������C�ʂɂ��Ȃ��ꍇ�C�ɖ߂�
		if (fish->CheckSeaSurface(player) == false &&
			fish->CheckSeaSurface(enemy[0]) == false &&
			fish->CheckSeaSurface(enemy[1]) == false &&
			fish->CheckSeaSurface(enemy[2]) == false)
		{
			fish->NotAtSeaSurface();
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

		//�v���C���[�̎c�@��0��菬�����ꍇ�^�C�g���ɖ߂�
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
	//�f�o�b�O�p�@�����蔻��\��
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

	//�X�R�A�\���i���j
	DrawNumber(0, 0, score);
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
