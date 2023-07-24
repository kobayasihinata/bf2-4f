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
	for (int i = 0; i < max_enemy; i++)
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
		//stagefloor�͈̔͂������[�v����
		for (BoxCollider* stagefloor : stagefloor)
		{
			//�v���C���[�����S���łȂ��Ȃ�
			if (player->GetPlayerDeathFlg() == false)
			{
				//�e�I�u�W�F�N�g�Ƃ̓����蔻�菈��
				player->HitStageCollision(stagefloor);				
			}

			//�v���C���[���ǂ̃I�u�W�F�N�g�Ƃ����n���Ă��Ȃ��ꍇ
			if (player->IsOnFloor(stagefloor) != true) {
				//onshare_flg��false�ɂ���
				player->SetOnShareFlg(false);
			}

			for (int i = 0; i < max_enemy; i++)
			{
				//�G�����S���łȂ��Ȃ�
				if (enemy[i]->GetEnemyDeathFlg() == false)
				{
					//�e�I�u�W�F�N�g�Ƃ̓����蔻�菈��
					enemy[i]->HitStageCollision(stagefloor);
					//�G��AI�擾
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

				//�G���ǂ̃I�u�W�F�N�g�Ƃ����n���Ă��Ȃ��ꍇ
				if (enemy[i]->IsOnFloor(stagefloor) != true) {
					//onshare_flg��false�ɂ���
					enemy[i]->SetOnShareFlg(false);
				}

				//�G�����S���[�V�������Ŗ������
				if (enemy[i]->GetEnemyDeathFlg() == false)
				{
					//�v���C���[�ƓG�̓����蔻��
					switch (player->HitEnemyCollision(enemy[i]))
					{
					case 1:
						player->ReflectionMX();
						enemy[i]->ReflectionPX();
						Damege(i);
						break;
					case 2:
						player->ReflectionPX();
						enemy[i]->ReflectionMX();
						Damege(i);
						break;
					case 3:
						player->ReflectionPY();
						enemy[i]->ReflectionMY();
						Damege(i);
						break;
					case 4:
						enemy[i]->ReflectionPY();
						player->ReflectionMY();
						Damege(i);
						break;
					default:
						break;
					}

					//�G�ƓG�̓����蔻��
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
					if (enemy[i]->GetShowFlg() == false)	//�O�̂���
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

		//�v���C���[�̎c�@��0��菬�����ꍇ�^�C�g���ɖ߂�
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
	//�f�o�b�O�p�@�����蔻��\��
	for (BoxCollider* stagefloor : stagefloor)
	{
		stagefloor->Draw();
	}
	if (Pouse == false) {
		player->Draw();
		for (int i = 0; i < max_enemy; i++)
		{
			enemy[i]->Draw();
		}
	}
	fish->Draw();
	DrawGraph(159, 444, seaImage, TRUE);

	//�X�R�A�\���i���j
	DrawFormatString(600, 0, 0x00ffff, "%d",score);
	DrawString(0, 0, "LB�{�^���F�G�P�Ƀ_���[�W", 0xff0000);
	DrawString(0, 20, "RB�{�^���F�G�Q�Ƀ_���[�W", 0xff0000);
	DrawString(0, 40, "���X�e�B�b�N�������݁F�G�R�Ƀ_���[�W", 0xff0000);
	DrawString(0, 60, "�E�X�e�B�b�N�������݁F�v���C���[�Ƀ_���[�W", 0xff0000);
}

void GameMain::Damege(int i)
{
	//�v���C���[��25��̍��W�ɓG������Ȃ�v���C���[�̕��D�����炷
	if (enemy[i]->GetLocation().y + BALLOON_HEIGHT < player->GetLocation().y)
	{
		player->BalloonDec();
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
