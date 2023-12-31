#include "Fish.h"
#include"Enemy.h"
#include"DxLib.h"
#include"Define.h"

//#define DEBUG

Fish::Fish()
{
	LoadDivGraph("images/Enemy/Enemy_FishAnimation.png", 10, 5, 2, 64, 64, fish_image);
	location.x = SEASURFACE_START_X;
	location.y = SEA_SURFACE;
	area.height = 55;
	area.width = 60;
	probability = 0;
	frame_count = 0;
	player_flying_on_sea_timer = SECOND_TO_FRAME(3);
	rising_timer = 0;
	fish_state = Rising_Fish_1;
	is_rising = false;
	is_falling = false;
	is_preying_on_player = false;
	is_preying_on_enemy = false;
	reversal_flg = false;
	respawn_flg = false;
	bubble_spawn_flg = true;
	target_flg = false;
	target_is_enemy = false;
	falling_anim = Falling_Fish_1;
	anim_frame = 0;
	Eatable_SE = LoadSoundMem("sounds /SE_Eatable.wav");
}

Fish::~Fish()
{

}

void Fish::Update()
{
	//さかなが海面の範囲内にいるなら
	if (GetMax().x <= SEASURFACE_END_X)
	{
		//泳いでいるなら
		if (is_rising == false && is_falling == false && is_preying_on_player == false && is_preying_on_enemy == false)
		{
			//右方向へ移動
			location.x++;
		}
	}
	//さかなが海面の範囲内にいないなら
	else
	{
		//泳いでいるなら
		if (is_rising == false && is_falling == false && is_preying_on_player == false && is_preying_on_enemy == false) 
		{
			//海面の範囲内へ戻す
			location.x = SEASURFACE_START_X;
		}
	}
#ifdef DEBUG
	//泳いでいるなら
	if (is_rising == false && is_falling == false && is_preying_on_player == false && is_preying_on_enemy == false)
	{
		//乱数を取得
		probability = 0;
	}
#else
	//泳いでいるなら
	if (is_rising == false && is_falling == false && is_preying_on_player == false && is_preying_on_enemy == false)
	{
		//乱数を取得
		probability = GetRand(99);
	}
#endif // DEBUG

	if (is_preying_on_player == true || is_preying_on_enemy == true)
	{
		speed = .6f;
	}

	if (is_rising == true && is_falling == true)
	{
		is_rising = false;
	}

	if (is_rising == true)
	{
		location.y -= speed;
		//0.6秒経過したら強制的に海面へ戻す
		if (++rising_timer > SECOND_TO_FRAME(0.8f))
		{
  			target_flg = true;
			is_rising = false;
		}
	}

	if (is_falling == true)
	{
		location.y += speed;
		fish_state = falling_anim;
		if (++anim_frame % 7 == 0)
		{
			if (falling_anim < Falling_Fish_3)
			{
				falling_anim += 1;
			}
		}
		//if (GetMax().y > SEA_SURFACE)
		//{
		//	fish_state = Falling_Fish_1;
		//}
		//if (GetMax().y - area.height / 4 > SEA_SURFACE)
		//{
		//	fish_state = Falling_Fish_2;
		//}
		//if (GetMax().y - area.height / 6 > SEA_SURFACE)
		//{
		//	fish_state = Falling_Fish_3;
		//}
		
	}

	if (location.y > SEA_SURFACE)
	{
		location.y = SEA_SURFACE;
		is_falling = false;
		is_preying_on_enemy = false;
		if (is_preying_on_player == true)
		{
			respawn_flg = true;
		}
		reversal_flg = false;
		fish_state = Rising_Fish_1;
#ifdef DEBUG
		player_flying_on_sea_timer = SECOND_TO_FRAME(-1);
#else
		player_flying_on_sea_timer = SECOND_TO_FRAME(3);
#endif // DEBUG
		rising_timer = 0;
		target_flg = false;
		target_is_enemy = false;
		anim_frame = 0;
		falling_anim = Falling_Fish_1;
		speed = 1.6f;
	}

	if (respawn_flg == true)
	{
		is_preying_on_player = false;
	}
}

void Fish::Draw()const
{
#ifdef DEBUG
	BoxCollider::Draw();
	DrawFormatString(0, 100, 0xff00ff, "%d", player_flying_on_sea_timer);
	DrawBox(SEASURFACE_START_X, SEA_SURFACE - PLAYER_ENEMY_HEIGHT, SEASURFACE_END_X, SCREEN_HEIGHT, 0xff0000, FALSE);
#endif // DEBUG

	if (reversal_flg == false)
	{
		DrawGraphF(location.x, location.y - IMAGE_SHIFT, fish_image[fish_state], TRUE);
	}
	else
	{
		DrawTurnGraphF(location.x, location.y - IMAGE_SHIFT, fish_image[fish_state], TRUE);
	}
}

void Fish::TargetPrey(BoxCollider* boxcollider)
{

	//さかなが何も捕食していないとき
	if (is_preying_on_player == false && is_preying_on_enemy == false &&
		boxcollider->GetIsDie() == false && target_flg == false)
	{
		player_flying_on_sea_timer--;
		//3秒以上かつ確率で
		if (player_flying_on_sea_timer < 0 && probability < 80)
		{
			//海面まで上がる処理
			if (GetMax().y > SEA_SURFACE)
			{
				//対象がさかなの中心より右にいるなら
				if (this->GetCenter().x <= boxcollider->GetMin().x)
				{
					//画像を反転させる
					reversal_flg = true; 
				}
				is_rising = true;
				location.x = boxcollider->GetCenter().x - area.width / 2;
				//location.y -= speed;				
				
				if (GetCenter().y < SEA_SURFACE)
				{
					fish_state = Rising_Fish_2;
					if ((GetCenter().y + area.height / 4)< SEA_SURFACE)
					{
						fish_state = Rising_Fish_3;
					}
				}
			}
			else
			{
				if (boxcollider->GetMin().x < this->GetMax().x && boxcollider->GetMax().x > this->GetMin().x &&
					this->GetMin().y <= boxcollider->GetMax().y)
				{
					if (boxcollider->GetIsPlayer() == true)
					{
						is_preying_on_player = true;
						fish_state = PreyingOn_Player;
						target_flg = true;
					}
					else
					{
						is_preying_on_enemy = true;
						if (GetSaveEnemyLevel() == 1)
						{
							if (CheckSoundMem(Eatable_SE) == FALSE) 
							{
								PlaySoundMem(Eatable_SE,DX_PLAYTYPE_BACK);
							}
							fish_state = PreyingOn_Enemy_1;
						}
						else if (GetSaveEnemyLevel() == 2)
						{
							if (CheckSoundMem(Eatable_SE) == FALSE) 
							{
								PlaySoundMem(Eatable_SE, DX_PLAYTYPE_BACK);
							}
							fish_state = PreyingOn_Enemy_2;
						}
						else
						{
							if (CheckSoundMem(Eatable_SE) == FALSE) 
							{
								PlaySoundMem(Eatable_SE, DX_PLAYTYPE_BACK);
							}
							fish_state = PreyingOn_Enemy_3;
						}
						target_flg = true;
					}
				}
				is_rising = false;
				is_falling = true;
			}
		}
	}
	
	if (boxcollider->GetIsDie() == true)
	{
		location.y += speed;
		fish_state = falling_anim;
		if (++anim_frame % 7 == 0)
		{
			if (falling_anim < Falling_Fish_3)
			{
				falling_anim += 1;
			}
		}

		//if (GetMax().y > SEA_SURFACE)
		//{
		//	fish_state = Falling_Fish_1;
		//}
		//if (GetMax().y - area.height / 4 > SEA_SURFACE)
		//{
		//	fish_state = Falling_Fish_2;
		//}
		//if (GetMax().y - area.height / 6 > SEA_SURFACE)
		//{
		//	fish_state = Falling_Fish_3;
		//}
	}
}


bool Fish::CheckSeaSurface(BoxCollider* boxcollider)
{
	bool ret = false;

	if (boxcollider->GetMin().x >= SEASURFACE_START_X && boxcollider->GetMax().x <= SEASURFACE_END_X &&
		boxcollider->GetMax().y > SEA_SURFACE - PLAYER_ENEMY_HEIGHT &&
		boxcollider->GetIsDie() == false && target_flg == false)
	{
		ret = true;
	}

	return ret;
}

void Fish::NotAtSeaSurface()
{
	is_falling = true;
	is_rising = false;
}

void Fish::SetTarget(BoxCollider* boxcollider)
{
	if (is_rising == true &&
		boxcollider->GetIsPlayer() == false)
	{
		target_is_enemy = true;
	}
}
