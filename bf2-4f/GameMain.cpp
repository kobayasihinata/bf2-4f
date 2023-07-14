#include "Dxlib.h"
#include "GameMain.h"
#include"Title.h"
#include"PadInput.h"


GameMain::GameMain()
{
	player = new Player();
	enemy = new Enemy(300,210,1);
	stagefloor[0] = new StageFloor(0, 416, 30, 160, 5);
	stagefloor[1] = new StageFloor(479, 416, 30, 160, 5);
	stagefloor[2] = new StageFloor(180, 260, 18, 280, 0);
	staegwall = new StageWall();
	fish = new Fish();
	seaImage = LoadGraph("images/Stage/Stage_Sea01.png");

	Pouse = false;
}

GameMain::~GameMain()
{
	delete player;
	delete enemy;
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

			//�e�I�u�W�F�N�g�Ƃ̓����蔻�菈��
			enemy->HitStageCollision(stagefloor);
		
			//�v���C���[���ǂ̃I�u�W�F�N�g�Ƃ����n���Ă��Ȃ��ꍇ
			if (player->IsOnFloor(stagefloor) != true) {
				//onshare_flg��false�ɂ���
				player->SetOnShareFlg(false);
			}

			//�G���ǂ̃I�u�W�F�N�g�Ƃ����n���Ă��Ȃ��ꍇ
			if (enemy->IsOnFloor(stagefloor) != true) {
				//onshare_flg��false�ɂ���
				enemy->SetOnShareFlg(false);
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
		//�G���e�I�u�W�F�N�g�̂����ꂩ�ɒ��n���Ă���ꍇ
		if (enemy->IsOnFloor(stagefloor[0]) == true ||
			enemy->IsOnFloor(stagefloor[1]) == true ||
			enemy->IsOnFloor(stagefloor[2]) == true)
		{
			//onshare_flg��true�ɂ���
			enemy->SetOnShareFlg(true);
		}
		player->Update();
		enemy->Update();
		enemy->EnemyMoveLeft();
		enemy->EnemyJump();
		fish->SetSaveEnemyLevel(enemy->GetEnemyLevel());
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
	if (Pouse == false) {
		player->Draw();
		enemy->Draw();
	}
	stagefloor[0]->DrawLandLeft();
	stagefloor[1]->DrawLandRight();
	stagefloor[2]->DrawFooting1();
	//�f�o�b�O�p�@�����蔻��\��
	for (BoxCollider* stagefloor : stagefloor)
	{
		stagefloor->Draw();
	}
	DrawString(0, 0, "�Q�[�����C��", 0xff0000);
	
	DrawGraph(159, 444, seaImage, TRUE);
	fish->Draw();
}