#include "Fish.h"
#include"Enemy.h"
#include"DxLib.h"
#include"Define.h"

Fish::Fish()
{
	LoadDivGraph("images/Enemy/Enemy_FishAnimation.png", 10, 6, 2, 64, 64, fish_image);
	location.x = SEASURFACE_START_X;
	location.y = UNDER_WATER;
	area.height = 55;
	area.width = 60;
	probability = 0;
	frame_count = 0;
	player_flying_on_sea_timer = SECOND_TO_FRAME(3);
	fish_state = Rising_Fish_1;
	is_rising = false;
	is_falling = false;
	is_preying_on_player = false;
	is_preying_on_enemy = false;
	reversal_flg = false;
	respawn_flg = false;
	bubble_spawn_flg = true;
	target_flg = false;
}

Fish::~Fish()
{

}

void Fish::Update()
{
	//Ç≥Ç©Ç»Ç™äCñ ÇÃîÕàÕì‡Ç…Ç¢ÇÈÇ»ÇÁ
	if (GetMax().x <= SEASURFACE_END_X)
	{
		//âjÇ¢Ç≈Ç¢ÇÈÇ»ÇÁ
		if (is_rising == false && is_falling == false && is_preying_on_player == false && is_preying_on_enemy == false)
		{
			//âEï˚å¸Ç÷à⁄ìÆ
			location.x++;
		}
	}
	//Ç≥Ç©Ç»Ç™äCñ ÇÃîÕàÕì‡Ç…Ç¢Ç»Ç¢Ç»ÇÁ
	else
	{
		//âjÇ¢Ç≈Ç¢ÇÈÇ»ÇÁ
		if (is_rising == false && is_falling == false && is_preying_on_player == false && is_preying_on_enemy == false) 
		{
			//äCñ ÇÃîÕàÕì‡Ç÷ñﬂÇ∑
			location.x = SEASURFACE_START_X;
		}
	}

	//âjÇ¢Ç≈Ç¢ÇÈÇ»ÇÁ
	if (is_rising == false && is_falling == false && is_preying_on_player == false && is_preying_on_enemy)
	{
		//óêêîÇéÊìæ
		probability = GetRand(99);
	}

	if (is_rising == true)
	{
		location.y -= speed;
	}

	if (is_falling == true)
	{
		location.y += speed;
		if (GetMax().y > SEA_SURFACE)
		{
			fish_state = Falling_Fish_1;
		}
		if (GetMax().y - area.height / 4 > SEA_SURFACE)
		{
			fish_state = Falling_Fish_2;
		}
		if (GetMax().y - area.height / 6 > SEA_SURFACE)
		{
			fish_state = Falling_Fish_3;
		}
	}

	if (location.y > UNDER_WATER)
	{
		location.y = UNDER_WATER;
		is_falling = false;
		is_preying_on_enemy = false;
		if (is_preying_on_player == true)
		{
			respawn_flg = true;
		}
		if (is_preying_on_enemy == true)
		{
			bubble_spawn_flg = false;
		}
		reversal_flg = false;
		fish_state = Rising_Fish_1;
		player_flying_on_sea_timer = SECOND_TO_FRAME(3);
		target_flg = false;
	}

	if (respawn_flg == true)
	{
		is_preying_on_player = false;
	}

	if (bubble_spawn_flg == false)
	{
		is_preying_on_enemy = false;
		//bubble_spawn_flg = true;
	}
}

void Fish::Draw()const
{
	//BoxCollider::Draw();
	//DrawFormatString(0, 100, 0xff00ff, "%d", player_flying_on_sea_timer);
	if (reversal_flg == false)
	{
		DrawGraphF(location.x, location.y - IMAGE_SHIFT, fish_image[fish_state], TRUE);
	}
	else
	{
		DrawTurnGraphF(location.x, location.y - IMAGE_SHIFT, fish_image[fish_state], TRUE);
	}
	//DrawBox(SEASURFACE_START_X, SEA_SURFACE - PLAYER_HEIGHT, SEASURFACE_END_X, SCREEN_HEIGHT, 0xff0000, FALSE);
}

void Fish::TargetPrey(BoxCollider* boxcollider)
{

	//Ç≥Ç©Ç»Ç™âΩÇ‡ïﬂêHÇµÇƒÇ¢Ç»Ç¢Ç∆Ç´
	if (is_preying_on_player == false && is_preying_on_enemy == false &&
		boxcollider->GetIsDie() == false && target_flg == false)
	{
		player_flying_on_sea_timer--;
		//3ïbà»è„Ç©Ç¬ämó¶Ç≈
		if (player_flying_on_sea_timer < 0 && probability < 80)
		{
			//äCñ Ç‹Ç≈è„Ç™ÇÈèàóù
			if (GetMax().y >= SEA_SURFACE)
			{
				//ëŒè€Ç™Ç≥Ç©Ç»ÇÃíÜêSÇÊÇËâEÇ…Ç¢ÇÈÇ»ÇÁ
				if (this->GetCenter().x <= boxcollider->GetMin().x)
				{
					//âÊëúÇîΩì]Ç≥ÇπÇÈ
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
							fish_state = PreyingOn_Enemy_1;
						}
						else if (GetSaveEnemyLevel() == 2)
						{
							fish_state = PreyingOn_Enemy_2;
						}
						else
						{
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
		location.y = location.y + speed;
		if (GetMax().y > SEA_SURFACE)
		{
			fish_state = Falling_Fish_1;
		}
		if (GetMax().y - area.height / 4 > SEA_SURFACE)
		{
			fish_state = Falling_Fish_2;
		}
		if (GetMax().y - area.height / 6 > SEA_SURFACE)
		{
			fish_state = Falling_Fish_3;
		}
	}
}


bool Fish::CheckSeaSurface(BoxCollider* boxcollider)
{
	bool ret = false;

	if (boxcollider->GetMin().x >= SEASURFACE_START_X && boxcollider->GetMax().x <= SEASURFACE_END_X &&
		boxcollider->GetMax().y > SEA_SURFACE - PLAYER_HEIGHT &&
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