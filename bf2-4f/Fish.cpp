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
	speed = 1.2f;
	frame_count = 0;
	player_flying_on_sea_timer = SECOND_TO_FRAME(3);
	fish_state = Rising_Fish_1;
	is_rising = false;
	is_falling = false;
	is_preying_on_player = false;
	is_preying_on_enemy = false;
	reversal_flg = false;
	respawn_flg = false;
}

Fish::~Fish()
{

}

void Fish::Update(BoxCollider* boxcollider)
{
	//Ç≥Ç©Ç»Ç™äCñ ÇÃîÕàÕì‡Ç…Ç¢ÇÈÇ»ÇÁ
	if (GetMax().x <= SEASURFACE_END_X)
	{
		//âjÇ¢Ç≈Ç¢ÇÈÇ»ÇÁ
		if (is_rising == false && is_falling == false && is_preying_on_player == false)
		{
			//âEï˚å¸Ç÷à⁄ìÆ
			location.x++;
		}
	}
	//Ç≥Ç©Ç»Ç™äCñ ÇÃîÕàÕì‡Ç…Ç¢Ç»Ç¢Ç»ÇÁ
	else
	{
		//âjÇ¢Ç≈Ç¢ÇÈÇ»ÇÁ
		if (is_rising == false && is_falling == false && is_preying_on_player == false)
		{
			//äCñ ÇÃîÕàÕì‡Ç÷ñﬂÇ∑
			location.x = SEASURFACE_START_X;
		}
	}

	//âjÇ¢Ç≈Ç¢ÇÈÇ»ÇÁ
	if (is_rising == false && is_falling == false && is_preying_on_player == false)
	{
		//óêêîÇéÊìæ
		probability = GetRand(99);
	}

	//ÉvÉåÉCÉÑÅ[Ç™äCñ Ç…Ç¢ÇÈÇ∆Ç´
	//ÉvÉåÉCÉÑÅ[Ç™äCñ Å{ÉvÉåÉCÉÑÅ[ÇÃçÇÇ≥ï™ÇÊÇËí·Ç≠îÚÇÒÇ≈Ç¢ÇÈÇ∆Ç´
	//Ç≥Ç©Ç»Ç™âΩÇ‡ïﬂêHÇµÇƒÇ¢Ç»Ç¢Ç∆Ç´
	if (boxcollider->GetMin().x >= SEASURFACE_START_X && boxcollider->GetMax().x <= SEASURFACE_END_X &&
		boxcollider->GetMax().y > SEA_SURFACE - PLAYER_ENEMY_HEIGHT &&
		is_preying_on_player == false && is_preying_on_enemy == false)
	{
		//3ïbà»è„Ç©Ç¬ämó¶Ç≈
		if (--player_flying_on_sea_timer < 0 && probability < 10)
		{
			//äCñ Ç‹Ç≈è„Ç™ÇÈèàóù
			if (GetMax().y >= SEA_SURFACE)
			{
				is_rising = true;
				location.x = boxcollider->GetCenter().x - area.width / 2;
				location.y -= speed;

				//ÉvÉåÉCÉÑÅ[Ç™Ç≥Ç©Ç»ÇÃíÜêSÇÊÇËâEÇ…Ç¢ÇÈÇ»ÇÁ
				if (this->GetCenter().x < boxcollider->GetMin().x)
				{
					//âÊëúÇîΩì]Ç≥ÇπÇÈ
   					reversal_flg = !reversal_flg;
				}
				
				if (GetCenter().y < SEA_SURFACE)
				{
					fish_state = Rising_Fish_2;
					if ((GetCenter().y + area.height / 4)< SEA_SURFACE)
					{
						fish_state = Rising_Fish_3;
					}
				}

				if (boxcollider->GetMax().y > GetMax().y)
				{
					/*ìGÇ™Ç≈Ç´éüëÊÇ±Ç±Ç…ÉvÉåÉCÉÑÅ[Ç©î€Ç©ÇÃîªíËÇÇ©Ç≠*/
					if (boxcollider->GetIsPlayer() == true)
					{
						fish_state = PreyingOn_Player;
					}
					else
					{
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
					}
					boxcollider->SetShowFlg(false);
				}
			}
			else
			{
				is_rising = false;
				is_preying_on_player = true;
			}
		}
	}
	else
	{
		is_falling = true;
		is_rising = false;
		player_flying_on_sea_timer = SECOND_TO_FRAME(3);
	}
	
	if (is_preying_on_player == true || is_falling == true)
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
		if (is_preying_on_player == true)
		{
			respawn_flg = true;
		}
		reversal_flg = false;
		fish_state = Rising_Fish_1;
	}

	if (respawn_flg == true)
	{
		is_preying_on_player = false;
	}
}

void Fish::Draw()const
{
	//BoxCollider::Draw();
	//DrawFormatString(0, 100, 0xff00ff, "%d", fish_state);
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