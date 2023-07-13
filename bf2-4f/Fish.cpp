#include "Fish.h"
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
	is_preyed_on_player = false;
	is_preyed_on_enemy = false;
	reversal_flg = false;
	respawn_flg = false;
}

Fish::~Fish()
{

}

void Fish::Update(BoxCollider* boxcollider)
{
	if (location.x + area.width <= SEASURFACE_END_X &&		//�����Ȃ��C�ʂ͈͓̔��ɂ���Ȃ�
		is_rising == false && is_preyed_on_player == false)	//�j���ł���Ȃ�
	{
		location.x++;	//�E�����ֈړ�
	}
	if (location.x + area.width >= SEASURFACE_END_X &&		//�����Ȃ��C�ʂ͈͓̔��𒴂�����
		is_rising == false && is_preyed_on_player == false)	//�j���ł���Ȃ�
	{
		location.x = SEASURFACE_START_X;	//�C�ʂ͈͓̔��֖߂�
	}

	if (is_rising == false && is_preyed_on_player == false)	//�j���ł���Ȃ�
	{
		//15�t���[�����Ƃ�
		if (++frame_count % 15 == 0)
		{
			probability = GetRand(99);		//�������擾
		}
	}

	//�C�ʂɂ���Ƃ�
	if (boxcollider->GetMin().x >= SEASURFACE_START_X && boxcollider->GetMax().x <= SEASURFACE_END_X &&
		boxcollider->GetMax().y > SEA_SURFACE - PLAYER_HEIGHT &&
		is_preyed_on_player == false)
	{
		//3�b�ȏォ�m����
		if (--player_flying_on_sea_timer < 0 && probability < 10)
		{
			//�オ�鏈��
			if (boxcollider->GetMax().y < location.y + area.height)
			{
				if (this->GetCenter().x < boxcollider->GetMin().x)
				{
   					reversal_flg = true;
				}
				if (this->GetCenter().x > boxcollider->GetMax().x)
				{
					reversal_flg = false;
				}
				is_rising = true;
				location.x = (boxcollider->GetLocation().x + boxcollider->GetArea().width / 2) - area.width / 2;
				location.y -= speed;

				if (location.y + area.height < SEA_SURFACE)
				{
					fish_state = Rising_Fish_2;
				}
				if (location.y + area.height < SEA_SURFACE - 10)
				{
					fish_state = Rising_Fish_3;
				}
			}
			else if (fish_state == Rising_Fish_1 || fish_state == Rising_Fish_2 || fish_state == PreyingOn_Player)
			{
				//�H�ׂ鏈��
				if (boxcollider->GetMax().y >= location.y + area.height)
				{//�v����
					location.y -= speed;
					/*�G���ł����悱���Ƀv���C���[���ۂ��̔��������*/
					fish_state = PreyingOn_Player;
					boxcollider->SetShowFlg(false);
					if (location.y + area.height < SEA_SURFACE)
					{
						is_rising = false;
						is_preyed_on_player = true;
					}
				}
			}
			else if (fish_state == Rising_Fish_3)
			{
				//�H�ׂ鏈��
				if (boxcollider->GetMax().y >= location.y)
				{
					/*�G���ł����悱���Ƀv���C���[���ۂ��̔��������*/
					fish_state = PreyingOn_Player;
					is_rising = false;
					is_preyed_on_player = true;
				}
			}
		}
	}
	else
	{
		is_falling = true;
		player_flying_on_sea_timer = SECOND_TO_FRAME(3);
	}
	
	if (is_preyed_on_player == true || is_falling == true)
	{
		location.y += speed;
		if (location.y + area.height > SEA_SURFACE - 10)
		{
			fish_state = Falling_Fish_1;
		}
		if (location.y + area.height > SEA_SURFACE - 5)
		{
			fish_state = Falling_Fish_2;
		}
		if (location.y + area.height > SEA_SURFACE)
		{
			fish_state = Falling_Fish_3;
		}
	}

	if (location.y>UNDER_WATER)
	{
		location.y = UNDER_WATER;
		is_falling = false;
		if (is_preyed_on_player == true)
		{
			respawn_flg = true;
		}
		reversal_flg = false;
		fish_state = Rising_Fish_1;
	}

	if (respawn_flg == true)
	{
		is_preyed_on_player = false;
	}
}

void Fish::Draw()const
{
	//BoxCollider::Draw();
	//DrawFormatString(0, 100, 0xff00ff, "%d", player_flying_on_sea_timer / 60);
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