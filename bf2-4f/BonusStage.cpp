#include"BonusStage.h"
#include "PadInput.h"

BonusStage::BonusStage()
{
	spawn_int = 0;
	player = new Player();
	stageobject = new StageObject();
	stageobject->SetInit(-1, 450, 30, 642, 5);
	ui = new UI();
	for (int i = 0; i < 20; i++)
	{
		balloon[i] = NULL;
	}
	spawn_balloon_count = 0;
	get_balloon_count = 0;
	result_flg = false;
	pause = false;
	add_once = false;
	play_once = false;
	result_time = 0;
	score = 0;
	wait_time = 0;
	LoadDivGraph("images/Player/Player_Animation.png", 31, 8, 4, 64, 64, player_image);
	LoadDivGraph("images/Title/Title_CursorAnimation.png", 4, 4, 1, 32, 64, balloon_image);

	trip_bgm = LoadSoundMem("sounds/BGM_Trip.wav");
	perfect_se = LoadSoundMem("sounds/SE_Perfect.wav");
	bubble_se = LoadSoundMem("sounds/SE_Bubble.wav");
	PlaySoundMem(trip_bgm, DX_PLAYTYPE_BACK);
}

BonusStage::~BonusStage()
{
	delete player;
	delete ui;
	for (int i = 0; i < 20; i++)
	{
		delete balloon[i];
	}
	DeleteSoundMem(trip_bgm);
	DeleteSoundMem(perfect_se);
}

AbstractScene* BonusStage::Update()
{
	if (result_flg == false)
	{
		if (PAD_INPUT::OnButton(XINPUT_BUTTON_START)) {
			pause = !pause;
		}
		if (pause == false) {

			player->Update();
			for (int i = 0; i < 20; i++)
			{
				if (balloon[i] != NULL)
				{
					balloon[i]->Update();
				}
			}

			//各オブジェクトとの当たり判定処理
			player->HitStageCollision(stageobject);

			//プレイヤーがいずれかのオブジェクトに着地していない場合
			if (player->IsOnFloor(stageobject) != true)
			{
				//onshare_flgをfalseにする
				player->SetOnShareFlg(false);
			}
			//プレイヤーが各オブジェクトのいずれかに着地している場合
			if (player->IsOnFloor(stageobject) == true)
			{
				//onshare_flgをtrueにする
				player->SetOnShareFlg(true);
			}

			for (int i = 0; i < 20; i++)
			{
				//プレイヤーと風船の当たり判定
				if (balloon[i] != NULL)
				{
					if (balloon[i]->HitPlayerCollision(player))
					{
						get_balloon_count++;
					}
				}
			}

			if (--spawn_int <= 0)
			{
				SpawnBalloon();
				spawn_int = GetRand(50) + 50;
			}

			if (EndCheck() == true)
			{
				StopSoundMem(trip_bgm);
				score = get_balloon_count * 300;
				result_flg = true;
			}
		}
	}
	else
	{
		result_time++;
		if (result_time > 60 && get_balloon_count == 20 && play_once == false)
		{
			PlaySoundMem(perfect_se, DX_PLAYTYPE_BACK);
			play_once = true;
		}
		if (result_time > 150)
		{
			if (result_time % 3 == 0)
			{
				if (score > 0)
				{
					score -= 100;
					PlaySoundMem(bubble_se, DX_PLAYTYPE_BACK);
					GameMain::AddScore(100);
				}
			}
			if (score == 0)
			{
				if (get_balloon_count == 20 && add_once == false && wait_time > 10)
				{
					GameMain::AddScore(10000);
					PlaySoundMem(bubble_se, DX_PLAYTYPE_BACK);
					add_once = true;
				}
				if (wait_time > 15)
				{
					StopSoundMem(bubble_se);
				}
				wait_time++;
				if (wait_time > 120)
				{
					return new GameMain(1);
				}
			}
		}

	}
	return this;
}

void BonusStage::Draw()const
{
	if (result_flg == false)
	{
		for (int i = 0; i < 20; i++)
		{
			if (balloon[i] != NULL)
			{
				balloon[i]->Draw();
			}
		}
		DrawBox(50, 400, 90, 460, 0x000000, true);
		DrawBox(150, 380, 190, 460, 0x000000, true);
		DrawBox(590, 400, 630, 460, 0x000000, true);
		DrawBox(490, 430, 530, 460, 0x000000, true);
		DrawBox(50, 400, 90, 460, 0xffff00, false);
		DrawBox(150, 380, 190, 460, 0xffff00, false);
		DrawBox(590, 400, 630, 460, 0xffff00, false);
		DrawBox(490, 430, 530, 460, 0xffff00, false);
		DrawBox(-1, 454, 641, 480, 0x000000, true);
		stageobject->Draw();
		player->Draw();
	}
	else
	{
		DrawTurnGraph(25, 125, player_image[0], TRUE);
		if (result_time < 40)
		{
			DrawGraph(135, 125, balloon_image[0], TRUE);
		}
		if (result_time >20)
		{
			SetFontSize(24);
			DrawString(200, 150,"×",0xffffff);
			DrawFormatString(260, 150, 0xffffff,"%d",get_balloon_count);
		}
		if (result_time > 40)
		{
			SetFontSize(24);
			DrawString(135, 150, "300", 0xffffff);
			DrawString(320, 150, "=", 0xffffff);
			DrawFormatString(350, 150, 0xffffff, "%4d PTS", score);
		}
		if (result_time > 60 && get_balloon_count == 20)
		{
			DrawString(95, 360, "P  E  R  F  E  C  T  ! ! !", 0xff0000);
			DrawString(75, 390, "SUPER  BONUS        10000PTS!", 0xff0000);
		}
	}
	ui->Draw(player->GetPlayerLife());
}

void BonusStage::SpawnBalloon()
{
	if (spawn_balloon_count < 20)
	{
		switch (GetRand(3))
		{
		case 0:
			balloon[spawn_balloon_count++] = new Balloon(50, 400);
			break;
		case 1:
			balloon[spawn_balloon_count++] = new Balloon(150, 380);
			break;
		case 2:
			balloon[spawn_balloon_count++] = new Balloon(590, 400);
			break;
		case 3:
			balloon[spawn_balloon_count++] = new Balloon(490, 430);
			break;
		}
	}
}

bool BonusStage::EndCheck()
{
	bool ret = true;
	//一個でもフラグが入っているなら偽を返す
	for (int i = 0; i < 20; i++)
	{
		if (balloon[i] == NULL)
		{
			ret = false;
		}
		if (balloon[i] != NULL)
		{
			if (balloon[i]->GetFlg() == true)
			{
				ret = false;
			}
		}
	}
	return ret;
}
