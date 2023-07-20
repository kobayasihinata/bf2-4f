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
	}
	stagefloor[0] = new StageFloor(0, 416, 30, 160, 5);
	stagefloor[1] = new StageFloor(479, 416, 30, 160, 5);
	stagefloor[2] = new StageFloor(180, 260, 18, 280, 0);
	staegwall = new StageWall();
	fish = new Fish();
	seaImage = LoadGraph("images/Stage/Stage_Sea01.png");

	Pouse = false;

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

			for (int i = 0; i < 3; i++)
			{
				//�G�����S���łȂ��Ȃ�
				if (enemy[i]->GetEnemyDeathFlg() == false)
				{
					//�e�I�u�W�F�N�g�Ƃ̓����蔻�菈��
					enemy[i]->HitStageCollision(stagefloor);
				}

				//�G���ǂ̃I�u�W�F�N�g�Ƃ����n���Ă��Ȃ��ꍇ
				if (enemy[i]->IsOnFloor(stagefloor) != true) {
					//onshare_flg��false�ɂ���
					enemy[i]->SetOnShareFlg(false);
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
		for (int i = 0; i < 3; i++)
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


			fish->SetSaveEnemyLevel(enemy[i]->GetEnemyLevel());
		}

		//�����p�_���[�W����
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_LEFT_SHOULDER))score += enemy[0]->ApplyDamege();
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_RIGHT_SHOULDER))score += enemy[1]->ApplyDamege();
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_LEFT_THUMB))score += enemy[2]->ApplyDamege();

		player->Update();
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
		for (int i = 0; i < 3; i++)
		{
			enemy[i]->Draw();
		}
	}
	DrawGraph(159, 444, seaImage, TRUE);
	fish->Draw();


	//�X�R�A�\���i���j
	DrawFormatString(600, 0, 0x00ffff, "%d",score);
	DrawString(0, 0, "LB�{�^���F�G�P�Ƀ_���[�W", 0xff0000);
	DrawString(0, 20, "RB�{�^���F�G�Q�Ƀ_���[�W", 0xff0000);
	DrawString(0, 40, "���X�e�B�b�N�������݁F�G�R�Ƀ_���[�W", 0xff0000);
	DrawString(0, 60, "�E�X�e�B�b�N�������݁F�v���C���[�Ƀ_���[�W", 0xff0000);
}
