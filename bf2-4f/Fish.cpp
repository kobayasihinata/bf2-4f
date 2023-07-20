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
}

Fish::~Fish()
{

}

void Fish::Update()
{
	//�����Ȃ��C�ʂ͈͓̔��ɂ���Ȃ�
	if (GetMax().x <= SEASURFACE_END_X)
	{
		//�j���ł���Ȃ�
		if (is_rising == false && is_falling == false && is_preying_on_player == false && is_preying_on_enemy == false)
		{
			//�E�����ֈړ�
			location.x++;
		}
	}
	//�����Ȃ��C�ʂ͈͓̔��ɂ��Ȃ��Ȃ�
	else
	{
		//�j���ł���Ȃ�
		if (is_rising == false && is_falling == false && is_preying_on_player == false && is_preying_on_enemy == false) 
		{
			//�C�ʂ͈͓̔��֖߂�
			location.x = SEASURFACE_START_X;
		}
	}

	//�j���ł���Ȃ�
	if (is_rising == false && is_falling == false && is_preying_on_player == false)
	{
		//�������擾
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
	}

	if (respawn_flg == true)
	{
		is_preying_on_player = false;
	}

	if (bubble_spawn_flg == false)
	{
		is_preying_on_enemy = false;
	}
}

void Fish::Draw()const
{
	//BoxCollider::Draw();
	DrawFormatString(0, 100, 0xff00ff, "%d", is_rising);
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

	//�v���C���[���C�ʂɂ���Ƃ�
	//�v���C���[���C�ʁ{�v���C���[�̍��������Ⴍ���ł���Ƃ�
	//�����Ȃ������ߐH���Ă��Ȃ��Ƃ�
	if (boxcollider->GetMin().x >= SEASURFACE_START_X && boxcollider->GetMax().x <= SEASURFACE_END_X &&
		boxcollider->GetMax().y > SEA_SURFACE - PLAYER_HEIGHT &&
		is_preying_on_player == false && is_preying_on_enemy == false &&
		boxcollider->GetIsDie() == false)
	{
		//3�b�ȏォ�m����
		if (--player_flying_on_sea_timer < 0 && probability < 10)
		{
			//�C�ʂ܂ŏオ�鏈��
			if (GetMax().y >= SEA_SURFACE)
			{
				is_rising = true;
				location.x = boxcollider->GetCenter().x - area.width / 2;
				//location.y -= speed;

				//�v���C���[�������Ȃ̒��S���E�ɂ���Ȃ�
				if (this->GetCenter().x < boxcollider->GetMin().x)
				{
					//�摜�𔽓]������
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
					is_rising = false;
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
				}
			}
			else
			{
				is_rising = false;
				is_falling = true;
				if (boxcollider->GetIsPlayer() == true)
				{
					is_preying_on_player = true;
				}
				else
				{
					is_preying_on_enemy = true;
				}
			}
		}
	}
	else
	{
		is_falling = true;
		is_rising = false;
		player_flying_on_sea_timer = SECOND_TO_FRAME(3);
	}
	
	if (is_falling == true)
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

	if (location.y > UNDER_WATER)
	{
		is_falling = false;
		location.y = UNDER_WATER;
		is_rising = false;
		is_preying_on_enemy = false;
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


bool Fish::CheckSeaSurface(BoxCollider* boxcollider)
{
	bool ret = false;

	if (boxcollider->GetMin().x >= SEASURFACE_START_X && boxcollider->GetMax().x <= SEASURFACE_END_X &&
		boxcollider->GetMax().y > SEA_SURFACE - PLAYER_HEIGHT &&
		is_preying_on_player == false && is_preying_on_enemy == false)
	{
		ret = true;
	}

	return ret;
}

void Fish::NotAtSeaSurface()
{
	is_falling = true;
	is_rising = false;
	player_flying_on_sea_timer = SECOND_TO_FRAME(3);
}